struct results {
    int start;
    int end;
    int value;
};

__kernel void maxSub( __global float* input, __global struct results* output, int n, int totalItems)
{
    int workID = get_global_id(0);
    
    int s,e;
    
    int stride = totalItems/n+1;
    int start = workID * stride;
    int end = start + stride;
    int max = input[start];
    
    if(start >= totalItems){
        output[workID].value = 0;
        output[workID].start = 0;
        output[workID].end = 0;
        
    }else {
        
        s= start;
        e = start;
    
        for( int i=start; i<end; i++){
            int sum = 0;
            for(int j=i; j<totalItems; j++){
                sum += input[j];
                if(sum > max){
                    max = sum;
                    s = i;
                    e = j;
                }
            }
        }

        output[workID].value = max;
        output[workID].start = s;
        output[workID].end = e;
    }
}