// Define the states as an enumerated type
typedef enum {
    HW_INIT,
    IDLE,
    DELIVERY,
    ERROR
} State;

int main() {
    State current_state = HW_INIT;  // Initial state

    while (1) { // Loop 
        switch (current_state) {
            case HW_INIT:
                if(BOTON_START==ON){
                    DISPLAY("Bienvenido");
                    VALVE(CLOSE);
                    current_state = IDLE;
                }
                break;

            case IDLE:
                DOSIS = GET_TECLA();

                if(LVL_H2O > min && TEMP_H2O < 40){               
                    HEATER(ON);
                    PUMP(ON);
                    TAPA(CLOSE);   
                }
                else {
                    if(TEMP_H20 = 40){
                        HEATER(OFF);
                        PUMP(OFF);
                        TAPA(OPEN);
                    }
                }
                
                if(LVL_H2O = min){
                    DISPLAY("Cargue Agua");
                    current_state = ERROR;
                    break;
                }

                if(PRES_CAPSULA==ON && DOSIS !=0){
                    TAPA(CLOSE);
                    AGUJAS(ON);
                    TIMER_RUN(DOSIS);
                    current_state = DELIVERY;
                    break;
                }
                break;

            case DELIVERY:
                VALVE(OPEN);
                PUMP(ON);
                HEATER(ON);

                if(TIMER_END()){
                    AGUJAS(OFF);
                    PUMP(OFF);
                    VALVE(CLOSE);
                    HEATER(OFF);
                    tapa(OPEN);
                    current_state = IDLE;
                    break;
                }

                if(LVL_H2O = min){
                    DISPLAY("Cargue Agua");
                    current_state = ERROR;
                    break;
                }
                break;

            case ERROR:
                if(LVL_H2O > min && BOTON_START==ON){
                    current_state = IDLE;
                }
                break;

            default:
                current_state = ERROR;
                break;
        }
    }

    return 0;
}