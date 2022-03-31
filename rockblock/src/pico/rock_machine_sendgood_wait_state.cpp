/*
    RockBLOCK Machine Send Bad State Implementation

    Indicates successful transmission
    
*/

#include "rock_machine_state.hpp"

// Setup a singleton
rock_machine_state* rock_machine_sendgood_wait_state::_instance = 0;

rock_machine_state* rock_machine_sendgood_wait_state::instance() {
    if(_instance == 0) {
        _instance = new rock_machine_sendgood_wait_state;
    }
    return _instance;
}

void rock_machine_sendgood_wait_state::send_ok(rock_machine* rock, char* response) {
    if(get_response(response, "OK") == ISBD_SUCCESS) {
        puts(response);
        cancel_alarm(rock->_timeout_id);
        // Increament message counter
        rock->inc_message_count();        
        // rock->_timeout_id = add_alarm_in_ms(GOOD_TIMEOUT, alarm_callback, NULL, false);                      
        change_state(rock, rock_machine_idle_wait_state::instance());
    }
}

// Change to next state on timeout
void rock_machine_sendgood_wait_state::repeat(rock_machine* rock) {
    puts("Device error");
    change_state(rock, rock_machine_idle_wait_state::instance()); 
}
