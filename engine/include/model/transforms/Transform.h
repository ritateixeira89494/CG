#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

class Transform {

    protected:
        float x;
        float z;
        float y;
    public:
        Transform(float x, float y, float z);
        virtual void apply() = 0;
};


#endif //__TRANSFORM_H__
