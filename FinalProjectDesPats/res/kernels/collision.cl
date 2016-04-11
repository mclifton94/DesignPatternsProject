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

__kernel void collision( __global struct pt* input, __global struct pt* output, int n, struct boundaries bounds, float gravity, bool release)
{
    int workID = get_global_id(0);
    
    float xAcc = 0;
    float yAcc = 0;
    float zAcc = 0;
    
    for(int i=0; i<n; i++){
        if( i != workID){
            float g = 0.00000000006674;
            float distX = input[i].x - input[workID].x;
            float distY = input[i].y - input[workID].y;
            float distZ = input[i].z - input[workID].z;
            float dist = distX*distX+distY*distY+distZ*distZ+.001;
            
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
            
            xAcc += f*distX/dist/input[workID].mass;
            yAcc += f*distY/dist/input[workID].mass;
            zAcc += f*distZ/dist/input[workID].mass;
        }
    }
    
    float suggestedXVelo = input[workID].direction.xValue - xAcc;
    float suggestedYVelo = input[workID].direction.yValue - gravity - yAcc;
    float suggestedZVelo = input[workID].direction.zValue - zAcc;

    float suggestedXPos =  input[workID].x - suggestedXVelo;
    float suggestedYPos = input[workID].y - suggestedYVelo;
    float suggestedZPos = input[workID].z - suggestedZVelo;
    
    if( !release){
        if( suggestedYPos <= bounds.BR.y ){
            suggestedYPos = bounds.BR.y;
            suggestedYVelo =  -.5*suggestedYVelo;
        }
        
        if( suggestedYPos >= bounds.TL.y ){
            suggestedYPos = bounds.TL.y;
            suggestedYVelo = -.5*suggestedYVelo;
        }

        if( suggestedXPos <= bounds.TL.x){
            suggestedXPos = bounds.TL.x;
            suggestedXVelo = -.75*suggestedXVelo;
        }
        
        if( suggestedXPos >= bounds.BR.x){
            suggestedXPos = bounds.BR.x;
            suggestedXVelo = -.75*suggestedXVelo;
        }
        
        if( suggestedZPos >= -1){
            suggestedZPos = -1;
            suggestedZVelo = -.5*suggestedZVelo;
        }
        
        if( suggestedZPos <= -2){
            suggestedZPos = -2;
            suggestedZVelo = -.5*suggestedZVelo;
        }
    }
    
    output[workID].x = suggestedXPos;
    output[workID].y = suggestedYPos;
    output[workID].z = suggestedZPos;
    
    output[workID].direction.xValue = suggestedXVelo;
    output[workID].direction.yValue = suggestedYVelo;
    output[workID].direction.zValue = suggestedZVelo;
    
}