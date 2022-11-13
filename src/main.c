// C or C++ code
#include <stdio.h>
#include <stdint.h>
#include "calculator.h"
#include "cov_base.h"

// no invalid expressions
#define expression_0 -1.2+2.4*(0.6-5.8)/2.9
#define expression_1 (-1.2+2.2)*(-3.4)-(5.8+3.20/2.4)*6.54
#define expression_2 (-1001.2)+2.25*(-3.4)*(5.8+2.4*795)
#define expression_3 -1.672+2.264842*(-3.4)*(5.8/2.4+6.0)
#define expression_4 -9.582+2.2*(-3.79874)*(5.8*2.4/8.85)
#define expression_5 3+4*5/(6.5/7*(6.8/(984/9.8)*6)+5)
#define expression_6 ((-72.6))+2.2*(-3.4/2.89*9)-(((((-5.8/2.4-6)))))
#define expression_7 -4.6/sin(20)*tan(7-80*4.6)+cos(5.9+cos(5.79-6)+1.2*tan(4.8-6.9/sin(20)/7.8-4.8))*3.8

#define expression_0_str "-1.2+2.4*(0.6-5.8)/2.9"
#define expression_1_str "(-1.2+2.2)*-3.4-(5.8+3.20/2.4)*6.54"
#define expression_2_str "(-1001.2)+2.25*(-3.4)*(5.8+2.4*795)"
#define expression_3_str "-1.672+2.264842*(-3.4)*(5.8/2.4+6.0)"
#define expression_4_str "-9.582+2.2*(-3.79874)*(5.8*2.4/8.85)"
#define expression_5_str "3+4*5/(6.5/7*(6.8/(984/9.8)*6)+5)"
#define expression_6_str "((-72.6))+2.2*-3.4/2.89*9-(((((-5.8/2.4-6)))))"
#define expression_7_str "-4.6/sin(20)*tan(7-80*4.6)+cos(5.9+cos(5.79-6)+1.2*tan(4.8-6.9/sin(20)/7.8-4.8))*3.8"

// note : expression_6_str 
// ((-72.6))+2.2*-3.4/2.89*9-(((((-5.8/2.4-6)))))     OK
// ((-72.6))+2.2*(-3.4/2.89*9)-(((((-5.8/2.4-6)))))   Cause error

/*
void __sanitizer_symbolize_pc(void *pc, const char *fmt, char *out_buf, size_t out_buf_size);

void __sanitizer_cov_trace_pc_guard(uint32_t *guard) 
{
    if (!*guard) return;
    void *PC = __builtin_return_address(0);
    char PcDescr[4096];

    // __sanitizer_symbolize_pc(PC, "%p %F %L", PcDescr, sizeof(PcDescr));
	__sanitizer_symbolize_pc(PC, "%L", PcDescr, sizeof(PcDescr));
    //printf("guard: %p %x PC %s\n", guard, *guard, PcDescr);

	//c_insert_code_pc_desc(PcDescr);
}*/


void compare(double result, const char expression[])
{
	double res = cal_exp(expression);
	printf("result = (%lf, %lf) %d\n", result, res, (result == res) ? 1 : 0);
}

int main(int argc, char* argv[])
{
	compare(expression_0, expression_0_str);
	compare(expression_1, expression_1_str);
	compare(expression_2, expression_2_str);
	compare(expression_3, expression_3_str);
	compare(expression_4, expression_4_str);
	compare(expression_5, expression_5_str);
	compare(expression_6, expression_6_str);
	//compare(expression_7, expression_7_str);

}
