#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

class Transform {

    protected:
        /*
         * x value of a transform.
         */
        float x;

        /*
         * y value of a transform.
         */
        float z;

        /*
         * z value of a transform.
         */
        float y;

        /**
         * Constructs a Transform.
         * @param x
         * @param y
         * @param z
         */
        Transform(float x, float y, float z);

    public:
        /**
         * Apply the transform.
         */
        virtual void apply() = 0;
};


#endif //__TRANSFORM_H__
