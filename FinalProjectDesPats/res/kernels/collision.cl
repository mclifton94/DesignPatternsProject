struct direct {
    float xValue;
    float yValue;
    float zValue;
};

struct pt {
    float x;
    float y;
    float z;
    float mass;
    struct direct direction;
};

struct boundaries {
    struct pt TL;
    struct pt BL;
    struct pt TR;
    struct pt BR;
};

__kernel void collision( __global struct pt* input, __global struct pt* output, int n, struct boundaries bounds, float gravity)
{
    int workID = get_global_id(0);
    
    float xAcc = 0;
    float yAcc = 0;
    
    for(int i=0; i<n; i++){
        if( i != workID){
            float g = 0.00000000006674;
            float distX = input[i].x - input[workID].x;
            float distY = input[i].y - input[workID].y;
            float dist = distX*distX+distY*distY+.01;
            
            float x = dist;
            float y = 1;
            float accuracy = 0.01;
            while(x - y > accuracy)
            {
                x = (x + y)/2;
                y = n/x;
            }
            
            dist = x;
            float f = g*input[i].mass*input[workID].mass/(dist*dist+.01);
            
            if(input[workID].x+xAcc != input[i].x){
                xAcc += f*distX/dist;
            }
            
            if(input[workID].y+yAcc != input[i].y){
                yAcc += f*distY/dist;
            }
        }
    }
    
    float suggestedXVelo = input[workID].direction.xValue - xAcc;
    float suggestedYVelo = input[workID].direction.yValue - gravity - yAcc;

    float suggestedXPos =  input[workID].x - suggestedXVelo;
    float suggestedYPos = input[workID].y - suggestedYVelo;
    
    if( suggestedYPos <= bounds.BR.y ){
        suggestedYPos = bounds.BR.y;
        suggestedYVelo = -.75*suggestedYVelo;
    }
    
    if( suggestedYPos > bounds.TL.y ){
        suggestedYPos = bounds.TL.y;
        suggestedYVelo = -.75*suggestedYVelo;
    }
    
    if( suggestedXPos < bounds.TL.x){
        suggestedXPos = bounds.TL.x;
        suggestedXVelo = -.75*suggestedXVelo;
    }
    
    if( suggestedXPos > bounds.BR.x){
        suggestedXPos = bounds.BR.x;
        suggestedXVelo = -.75*suggestedXVelo;
    }

    if(output[workID].direction.xValue == 0 && output[workID].direction.yValue == 0 && output[workID].direction.zValue == 0){
        output[workID].direction.yValue = suggestedYVelo;
    }
    
    output[workID].x = suggestedXPos;
    output[workID].y = suggestedYPos;
    
    output[workID].direction.xValue = suggestedXVelo;
    output[workID].direction.yValue = suggestedYVelo;
    
}