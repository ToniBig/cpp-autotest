#pragma once

#define _CONCATENATE_IMPL(s1, s2) s1##s2
#define CONCATENATE(s1, s2) _CONCATENATE_IMPL(s1, s2)
#define STR(str) #str
