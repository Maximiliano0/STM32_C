// Define the states as an enumerated type
typedef enum {
    HW_INIT,
    IDLE,
    DELIVERY,
    ERROR
} State;

// Function prototypes for each state's handler
State handle_hw_init();
State handle_idle();
State handle_delivery();
State handle_error();

// State function pointer type
typedef State (*StateHandler)();

// State transition table
StateHandler state_table[] = {
    handle_hw_init,
    handle_idle,
    handle_delivery,
    handle_error
};

int main() {
    State current_state = HW_INIT;  // Initial state

    while (1) {
        current_state = state_table[current_state]();  // Call the appropriate state handler
    }

    return 0;
}

// State handler functions
State handle_hw_init() {
    if (BOTON_START == ON) {
        DISPLAY("Bienvenido");
        VALVE(OFF);
        return IDLE;
    }
    return HW_INIT;
}

State handle_idle() {
    int DOSIS = GET_TECLA();

    if (LVL_H2O > min && TEMP_H2O < 40) {
        HEATER(ON);
        PUMP(ON);
        TAPA(OFF);
    } else if (TEMP_H2O == 40) {
        HEATER(OFF);
        PUMP(OFF);
        TAPA(ON);
    }

    if (LVL_H2O <= min) {
        DISPLAY("Cargue Agua");
        return ERROR;
    }

    if (PRES_CAPSULA == ON && DOSIS != 0) {
        TAPA(OFF);
        AGUJAS(ON);
        TIMER_RUN(DOSIS);
        return DELIVERY;
    }

    return IDLE;
}

State handle_delivery() {
    VALVE(ON);
    PUMP(ON);
    HEATER(ON);

    if (TIMER_END()) {
        AGUJAS(OFF);
        PUMP(OFF);
        VALVE(OFF);
        HEATER(OFF);
        TAPA(ON);
        return IDLE;
    }

    if (LVL_H2O <= min) {
        DISPLAY("Cargue Agua");
        return ERROR;
    }

    return DELIVERY;
}

State handle_error() {
    if (LVL_H2O > min && BOTON_START == ON) {
        return IDLE;
    }
    return ERROR;
}
