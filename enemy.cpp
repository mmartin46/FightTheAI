#include "enemy.hpp"

Enemy::Enemy()
{
    setDamage(0);
    functionality = 1;
    frame = 1;
    setFacingLeft(false);
}

template <typename T>
void Enemy::setupTarget(T &plyr)
{
    target.p1_x = plyr.get_x();
    target.p1_y = plyr.get_y();
    target.p2_x = get_x();
    target.p2_y = get_y();

}

bool Enemy::usePunchAttack(const CollisionStruct &collision, Player *plyr)
{
    if ( (abs(collision.x1 - collision.x2) <= 10) &&
         (abs(collision.y1 - collision.y2) <= 10) )
    {
        plyr->incDamage();
        setDoAttack_0();
        if (getFacingLeft())
        {
            plyr->set_dx(-1.3 * getDamage());
            plyr->set_dy(-1.2 * getDamage());
        }
        else
        {
            plyr->set_dx(1.3 * getDamage());
            plyr->set_dy(-1.2 * getDamage());                
        }  
        return true;   
    }
    return false;   
}

bool Enemy::useSpinAttack(const CollisionStruct &collision, Player *plyr)
{

        if (getFrame() >= 8 && getFrame() <= 13)
        {
            if ( (abs(collision.x1 - collision.x2) <= 10) &&
                (abs(collision.y1 - collision.y2) <= 10) )
            {
                plyr->incDamage();
            
                setDoAttack_1();
                if (getFacingLeft())
                {
                    plyr->set_dx(-1.2 * plyr->getDamage());
                    plyr->set_dy(-1.3 * plyr->getDamage());
                }
                else
                {
                    plyr->set_dx(1.2 * plyr->getDamage());
                    plyr->set_dy(-1.3 * plyr->getDamage());                
                }
                return true;    
            } 
        }
        return false;
}


constexpr unsigned int hash(const char *s, int off = 0)
{
    return !s[off] ? 5382 : (hash(s, off+1)*33) ^ s[off];
}

void Enemy::movement()
{
    // Right
    states["RIGHT"] = get_distances(target.p1_x - 10, target.p2_x, target.p1_y, target.p2_y);
    // Down
    states["DOWN"] = get_distances(target.p1_x, target.p2_x, target.p1_y - 10, target.p2_y);
    // Left
    states["LEFT"] = get_distances(target.p1_x + 10, target.p2_x, target.p1_y, target.p2_y);
    // Up
    states["UP"] = get_distances(target.p1_x, target.p2_x, target.p1_y + 10, target.p2_y);

    // Up-Right
    states["UPRIGHT"] = get_distances(target.p1_x - 10, target.p2_x, target.p1_y + 10, target.p2_y);
    // Up-Left
    states["UPLEFT"] = get_distances(target.p1_x + 10, target.p2_x, target.p1_y + 10, target.p2_y);
    // Down-Right
    states["DOWNRIGHT"] = get_distances(target.p1_x - 10, target.p2_x, target.p1_y - 10, target.p2_y);
    // Down-Left
    states["DOWNLEFT"] = get_distances(target.p1_x + 10, target.p2_x, target.p1_y - 10, target.p2_y);
    std::pair<std::string, double> heuristic = *std::min_element(states.begin(), states.end(), comp());



    if (heuristic.second >= 20 && getFunctionality())
    {

        switch (hash(heuristic.first.c_str()))
        {
            case hash("LEFT") : {
                setMovingLeft();
                leftMovement(0.2);
            }
            break;
            case hash("RIGHT") : {
                setMovingRight();
                rightMovement(0.2);
            }
            break;
            case hash("DOWN") : {
                setMovingDown();
                rightMovement(0.2);
            }
            break;
            case hash("UP") : {
                setMovingUp();
                applyJump();
                upMovement(-10);
            }
            break;
            case hash("UPLEFT") : {
                upMovement(-10);
                leftMovement(0.2);
            }
            break;
            case hash("UPRIGHT") : {
                upMovement(-10);
                rightMovement(0.2);
            }
            break;
            case hash("DOWNLEFT") : {
                downMovement();
                leftMovement(0.2);            
            }
            break;
            case hash("DOWNRIGHT") : {
                downMovement();
                rightMovement(0.2);
            }
            break;
        }
    }
    else
    {
        set_dx(0);
        set_dy(0);
        resetDoAttack_0();
        resetDoAttack_1();
    }

}