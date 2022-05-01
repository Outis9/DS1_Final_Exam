//
// Created by Kevin on 2022/4/21.
//

#ifndef DS1FINALPROJECT2_TUBE_H
#define DS1FINALPROJECT2_TUBE_H

enum Result{
    NEGATIVE, POSITIVE, SUSPECT, CLOSECONTACT, SUB_CLOSECONTACT, WAITING, INQUEUE, NOTCHECKED
};

class Tube {
public:
    std::string tube_id="00000";
    std::string tube_state;
};


#endif //DS1FINALPROJECT2_TUBE_H
