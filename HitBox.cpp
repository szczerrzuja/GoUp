#include "HitBox.h"
HitBox::HitBox(glm::vec3 *Pos, glm::vec3 lenghtInAxis)
{
	this->Position = Pos;
	Half_size = { lenghtInAxis.x / 2,  lenghtInAxis.y / 2, lenghtInAxis.z / 2 };

}
HitBox::HitBox()
{
   
}
HitBox::~HitBox()
{

};

bool HitBox::getColision(HitBox& box2)
{

    return ((Position->x - Half_size.x <= box2.Position->x + box2.Half_size.x  && Position->x + Half_size.x >= box2.Position->x - box2.Half_size.x)
        && (Position->y - Half_size.y <= box2.Position->y + box2.Half_size.y   && Position->y + Half_size.y >= box2.Position->y - box2.Half_size.y)
        && (Position->z - Half_size.z <= box2.Position->z + box2.Half_size.z   && Position->z + Half_size.z >= box2.Position->z - box2.Half_size.z));
}
void HitBox::scale(glm::vec3 sca)
{
    Half_size *= sca;
}
