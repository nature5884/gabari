//
//  ResultBoard.hpp
//  Gabari
//
//  Created by 蔵元隼人 on 2017/01/12.
//
//

#ifndef ResultBoard_hpp
#define ResultBoard_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "TalkLabel.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ResultBoard : public Node
{
public:
    static ResultBoard *create(int score);
    bool init(int score);
    void update(float delta);
    
    Scale9Sprite *_backBoard;
    TalkLabel *frontLb,*scoreLb;
    
private:
    void setupBoard();
    void makeScoreText();
    
    int _score;
    
    
};

#endif /* ResultBoard_hpp */
