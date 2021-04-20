#include "combine.h"

/* Combining functions */

char inner1_descr[] = "inner1: original loop no unrolling";
/* $begin inner1 */
void inner1(vec_ptr u, vec_ptr v, data_t *dest)
{
long int i;
int length = vec_length(u);
data_t *udata = get_vec_start(u);
data_t *vdata = get_vec_start(v);
data_t sum = (data_t) 0;
for (i=0;i<length;i++){
    sum = sum + udata[i] * vdata[i];
    }
*dest = sum;
}


char inner2_descr[] = "inner2: unroll 2x and 2 accumulators"; 
/* $begin inner2 */
void inner2(vec_ptr u, vec_ptr v, data_t *dest)
{
long int i;
int length = vec_length(u);
data_t *udata = get_vec_start(u);
data_t *vdata = get_vec_start(v);
data_t sum = (data_t) 0;
data_t sum2 = 0;
length = length - 2;
for (i=0;i<length;i+=2){
    sum = sum + udata[i] * vdata[i];
    sum2 = sum2 + udata[i+1] * vdata[i+1];
    }
length+=2;
for(;i<length;i++)
    sum = sum + udata[i] * vdata[i];
*dest = sum + sum2;
}


char inner4_descr[] = "inner4: unroll 4x and 4 accumulators"; 
/* $begin inner4 */
void inner4(vec_ptr u, vec_ptr v, data_t *dest)
{
long int i;
int length = vec_length(u);
data_t *udata = get_vec_start(u);
data_t *vdata = get_vec_start(v);
data_t sum = (data_t) 0;
data_t sum2 = 0;
data_t sum3 = 0;
data_t sum4 = 0;
length -= 4;
for (i=0;i<length;i+=4){
    sum = sum + udata[i] * vdata[i];
    sum2 = sum2 + udata[i+1] * vdata[i+1];
    sum3 = sum3 + udata[i+2] * vdata[i+2];
    sum4 = sum4 + udata[i+3] * vdata[i+3];
    }
length += 4;
for(;i<length;i++)
    sum = sum + udata[i] * vdata[i];
sum += sum2;
sum3 += sum4;
*dest = sum + sum3;
}

char inner8_descr[] = "inner8: unroll 8x and 8 accumulators"; 
/* $begin inner8 */
void inner8(vec_ptr u, vec_ptr v, data_t *dest)
{
long int i;
int length = vec_length(u);
data_t *udata = get_vec_start(u);
data_t *vdata = get_vec_start(v);
data_t sum = (data_t) 0;
data_t sum2 = 0;
data_t sum3 = 0;
data_t sum4 = 0;
data_t sum5 = 0;
data_t sum6 = 0;
data_t sum7 = 0;
data_t sum8 = 0;

length -= 8;
for (i=0;i<length;i+=8){
    sum = sum + udata[i] * vdata[i];
    sum2 = sum2 + udata[i+1] * vdata[i+1];
    sum3 = sum3 + udata[i+2] * vdata[i+2];
    sum4 = sum4 + udata[i+3] * vdata[i+3];
    sum5 = sum5 + udata[i+4] * vdata[i+4];
    sum6 = sum6 + udata[i+5] * vdata[i+5];
    sum7 = sum7 + udata[i+6] * vdata[i+6];
    sum8 = sum8 + udata[i+7] * vdata[i+7];
    }
length += 8;
for(;i<length;i++)
    sum = sum + udata[i] * vdata[i];
sum += sum2;
sum3 += sum4;
sum5 += sum6;
sum7 += sum8;
sum += sum3;
sum5 += sum7;
*dest = sum + sum5;
}




void register_combiners(void)
{
    add_combiner(inner1, inner1, inner1_descr);
    add_combiner(inner2, inner1, inner2_descr);
    add_combiner(inner4, inner1, inner4_descr);
    add_combiner(inner8, inner1, inner8_descr);
}
/*
m32
Float Sum inner1: original loop no unrolling:
8.07 cycles/element
Float Sum inner2: unroll 2x and 2 accumulators:
4.87 cycles/element
Float Sum inner4: unroll 4x and 4 accumulators:
4.30 cycles/element
Float Sum inner8: unroll 8x and 8 accumulators:
3.98 cycles/element

m32
Integer Sum inner1: original loop no unrolling:
6.72 cycles/element
Integer Sum inner2: unroll 2x and 2 accumulators:
4.57 cycles/element
Integer Sum inner4: unroll 4x and 4 accumulators:
4.12 cycles/element
Integer Sum inner8: unroll 8x and 8 accumulators:
3.83 cycles/element

m64
Float Sum inner1: original loop no unrolling:
7.26 cycles/element
Float Sum inner2: unroll 2x and 2 accumulators:
4.84 cycles/element
Float Sum inner4: unroll 4x and 4 accumulators:
4.27 cycles/element
Float Sum inner8: unroll 8x and 8 accumulators:
3.97 cycles/element

m64
Integer Sum inner1: original loop no unrolling:
6.34 cycles/element
Integer Sum inner2: unroll 2x and 2 accumulators:
4.57 cycles/element
Integer Sum inner4: unroll 4x and 4 accumulators:
4.15 cycles/element
Integer Sum inner8: unroll 8x and 8 accumulators:
3.87 cycles/element
*/
