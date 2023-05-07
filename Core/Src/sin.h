/*
 * sin.h
 *
 *  Created on: May 3, 2023
 *      Author: colecosta7
 */

#ifndef SRC_SIN_H_
#define SRC_SIN_H_

static const uint16_t sineTable100[] = {
		1500,

		1522,1544,1567,1589,1612,1634,1656,1679,1701,1723,

		1745,1767,1789,1811,1833,1855,1877,1899,1920,1942,

		1963,1984,2005,2027,2048,2068,2089,2110,2130,2150,

		2170,2190,2210,2230,2250,2269,2288,2307,2326,2344,

		2363,2381,2399,2417,2435,2452,2469,2486,2503,2520,

		2536,2552,2568,2584,2599,2614,2629,2644,2658,2672,

		2686,2700,2713,2726,2739,2751,2764,2776,2787,2799,

		2810,2820,2831,2841,2851,2861,2870,2879,2887,2896,

		2904,2912,2919,2926,2933,2939,2945,2951,2957,2962,

		2967,2971,2975,2979,2983,2986,2989,2991,2993,2995,

		2997,2998,2999,2999,2999,2999,2999,2998,2997,2995,

		2993,2991,2989,2986,2983,2979,2975,2971,2967,2962,

		2957,2951,2945,2939,2933,2926,2919,2912,2904,2896,

		2887,2879,2870,2861,2851,2841,2831,2820,2810,2799,

		2787,2776,2764,2751,2739,2726,2713,2700,2686,2672,

		2658,2644,2629,2614,2599,2584,2568,2552,2536,2520,

		2503,2486,2469,2452,2435,2417,2399,2381,2363,2344,

		2326,2307,2288,2269,2249,2230,2210,2190,2170,2150,

		2130,2110,2089,2068,2048,2027,2005,1984,1963,1942,

		1920,1899,1877,1855,1833,1811,1789,1767,1745,1723,

		1701,1679,1656,1634,1612,1589,1567,1544,1522,1500,

		1478,1456,1433,1411,1388,1366,1344,1321,1299,1277,

		1255,1233,1211,1189,1167,1145,1123,1101,1080,1058,

		1037,1016,994,973,952,932,911,890,870,850,

		830,810,790,770,750,731,712,693,674,656,

		637,619,601,583,565,548,531,514,497,480,

		464,448,432,416,401,386,371,356,342,328,

		314,300,287,274,261,249,236,224,213,201,

		190,180,169,159,149,139,130,121,113,104,

		96,88,81,74,67,61,55,49,43,38,

		33,29,25,21,17,14,11,9,7,5,

		3,2,1,1,1,1,1,2,3,5,

		7,9,11,14,17,21,25,29,33,38,

		43,49,55,61,67,74,81,88,96,104,

		113,121,130,139,149,159,169,180,190,201,

		213,224,236,249,261,274,287,300,314,328,

		342,356,371,386,401,416,432,448,464,480,

		497,514,531,548,565,583,601,619,637,656,

		674,693,712,731,751,770,790,810,830,850,

		870,890,911,932,953,973,995,1016,1037,1058,

		1080,1101,1123,1145,1167,1189,1211,1233,1255,1277,

		1299,1321,1344,1366,1388,1411,1433,1456,1478
};

static const int16_t sineTable200[] = {
		1500,

		1544,1589,1634,1679,1723,1767,1811,1855,1899,1942,

		1984,2027,2068,2110,2150,2190,2230,2269,2307,2344,

		2381,2417,2452,2486,2520,2552,2584,2614,2644,2672,

		2700,2726,2751,2776,2799,2820,2841,2861,2879,2896,

		2912,2926,2939,2951,2962,2971,2979,2986,2991,2995,

		2998,2999,2999,2998,2995,2991,2986,2979,2971,2962,

		2951,2939,2926,2912,2896,2879,2861,2841,2820,2799,

		2776,2751,2726,2700,2672,2644,2614,2584,2552,2520,

		2486,2452,2417,2381,2344,2307,2269,2230,2190,2150,

		2110,2068,2027,1984,1942,1899,1855,1811,1767,1723,

		1679,1634,1589,1544,1500,1456,1411,1366,1321,1277,

		1233,1189,1145,1101,1058,1016,973,932,890,850,

		810,770,731,693,656,619,583,548,514,480,

		448,416,386,356,328,300,274,249,224,201,

		180,159,139,121,104,88,74,61,49,38,

		29,21,14,9,5,2,1,1,2,5,

		9,14,21,29,38,49,61,74,88,104,

		121,139,159,180,201,224,249,274,300,328,

		356,386,416,448,480,514,548,583,619,656,

		693,731,770,810,850,890,932,973,1016,1058,

		1101,1145,1189,1233,1277,1321,1366,1411,1456
};

static const int16_t sineTable300[] = {

		1500,

		1567,1634,1701,1767,1833,1899,1963,2027,2089,2150,

		2210,2269,2326,2381,2435,2486,2536,2584,2629,2672,

		2713,2751,2787,2820,2851,2879,2904,2926,2945,2962,

		2975,2986,2993,2998,2999,2998,2993,2986,2975,2962,

		2945,2926,2904,2879,2851,2820,2787,2751,2713,2672,

		2629,2584,2536,2486,2435,2381,2326,2269,2210,2150,

		2089,2027,1963,1899,1833,1767,1701,1634,1567,1500,

		1433,1366,1299,1233,1167,1101,1037,973,911,850,

		790,731,674,619,565,514,464,416,371,328,

		287,249,213,180,149,121,96,74,55,38,

		25,14,7,2,1,2,7,14,25,38,

		55,74,96,121,149,180,213,249,287,328,

		371,416,464,514,565,619,674,731,790,850,

		911,973,1037,1101,1167,1233,1299,1366,1433
};

static const int16_t sineTable400[] = {
		1500,

		1589,1679,1767,1855,1942,2027,2110,2190,2269,2344,

		2417,2486,2552,2614,2672,2726,2776,2820,2861,2896,

		2926,2951,2971,2986,2995,2999,2998,2991,2979,2962,

		2939,2912,2879,2841,2799,2751,2700,2644,2584,2520,

		2452,2381,2307,2230,2150,2068,1984,1899,1811,1723,

		1634,1544,1456,1366,1277,1189,1101,1016,932,850,

		770,693,619,548,480,416,356,300,249,201,

		159,121,88,61,38,21,9,2,1,5,

		14,29,49,74,104,139,180,224,274,328,

		386,448,514,583,656,731,810,890,973,1058,

		1145,1233,1321,1411
};

static const int16_t sineTable500[] = {
		1500,

		1612,1723,1833,1942,2048,2150,2250,2344,2435,2520,

		2599,2672,2739,2799,2851,2896,2933,2962,2983,2995,

		2999,2995,2983,2962,2933,2896,2851,2799,2739,2672,

		2599,2520,2435,2344,2249,2150,2048,1942,1833,1723,

		1612,1500,1388,1277,1167,1058,952,850,750,656,

		565,480,401,328,261,201,149,104,67,38,

		17,5,1,5,17,38,67,104,149,201,

		261,328,401,480,565,656,751,850,953,1058,

		1167,1277,1388
};

#endif /* SRC_SIN_H_ */