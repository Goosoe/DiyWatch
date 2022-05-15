#include "ScreenController.h"
#include "TimeDisplay.h"
#include "Util.h"

namespace screenController{
    void setup(){
        timeDisplay::setup();
    }
    
    void update(const int currentTime, const stateUtil::MODE mode){ //TODO: state mode must be specific to different modules
        timeDisplay::update(currentTime, mode);
    }

    /**
     * @brief Set the Editable Field object
     * @param field 
     */
    void setEditableField(const uint8_t field){
        if(field < 2){   //0 = hours, 1 = minutes
            timeDisplay::setEditableField(field);
        }
    }

    void drawTime(const uint8_t* timeArr){
        timeDisplay::drawNumbers(timeArr);
    }
    
} // namespace screenController
