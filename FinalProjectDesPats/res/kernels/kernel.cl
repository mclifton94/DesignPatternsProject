typedef struct sqr
    {
        float xCenter;
        float yCenter;
        float scale;
        
    } sqr;

__kernel void square( __global float* input, __global float* output, const unsigned int count)
{
    int i = get_global_id(0);
    if(i < count){
        output[i] = input[i] * input[i];
    }
}

__kernel void doubleValue(__global float* input, __global float* output, const unsigned int count)
{
    int i = get_global_id(0);
    if(i<count){
        output[i] = input[i] + input[i];
    }
    
    
}