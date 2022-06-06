#include <stdio.h>
#include <stdlib.h>

int* generate_ref_arr(size_t sz, size_t page_max);
int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz);

int _contains(int* ref_arr, size_t sz, int target);
// Driver code
//  Usage: ./program {ref_arr_size} {page_max} {frame_size}
int main(int argc, char** argv) {
    if (argc < 4) return -1;
    
    int ref_arr_sz = atoi(argv[1]);
    int page_max = atoi(argv[2]);
    int frame_sz = atoi(argv[3]);

    int* ref = generate_ref_arr(ref_arr_sz, page_max);
    int page_faults = lru(ref, ref_arr_sz, frame_sz);
    printf("%d\n", page_faults);
    free(ref);

    return 0;
}

int* generate_ref_arr(size_t sz, size_t page_max) {
    int* ref_arr = (int*) malloc(sizeof(int) * sz);
    
    // TODO :: Generate Random Refernece String

    int max = page_max;
    for(int i = 0; i < sz; i++){
	    ref_arr[i] = rand() % max;
    }
    return ref_arr;
}

int lru(int* ref_arr, size_t ref_arr_sz, size_t frame_sz) {
    int i, j;
    int page_faults = 0;
    
    // Initializing frames
    int* frames = (int*) malloc(sizeof(int) * frame_sz);
    for (i=0; i<frame_sz; i++) frames[i] = -1;

    // TODO

    int is_fault;
    int target = 0, top = 0;

    int pt = 0;
    int* ref_bit = (int*)malloc(sizeof(int) * frame_sz);
    for(i = 0; i < frame_sz; i++) ref_bit[i] = 0;
  
    for(i = 0; i <ref_arr_sz; i++){
	    is_fault = _contains(frames, frame_sz, ref_arr[i]);
	    if(is_fault == -1){
		    if(top < frame_sz){
			    frames[target] = ref_arr[i];
			    ref_bit[target] = 0;
			    target = (target + 1) % frame_sz;
			    top++;
		    }
		    else {
			    while (1) {
				    if(ref_bit[pt] == 0){
					    target = pt;
					    pt++;
					    break;
				    }
				    else if(ref_bit[pt] == 1) {
					    ref_bit[pt] = 0;
				    }
				    pt++;
				    if(pt > frame_sz) pt = 0;
			    }
			    frames[target] = ref_arr[i];
		    }
		    page_faults++;
	    }
	    else {
		    frames[is_fault] = ref_arr[i];
		    ref_bit[is_fault] = 1;
	    }
    }

    return page_faults;
}

int _contains(int* arr, size_t sz, int target){
	int i = 0;
	for ( i = 0; i <sz; i++){
		if(arr[i] == target) return i;
	}
	return -1;
}
