///                MentOS, The Mentoring Operating system project
/// @file deadlock_prevention.c
/// @brief Deadlock prevention algorithms source code.
/// @copyright (c) 2019 This file is distributed under the MIT License.
/// See LICENSE.md for details.
///
/// Complete request() and state_safe() functions, according to what you learnt
/// in deadlock lectures.
///
/// In order to complete the functions I prepared for you a library to manage
/// easily arrays. The library is arr_math.h and you can find the documentation
/// in include/util/arr_math.h header file.
///
/// In addition you will find the same data structures that you have seen in
/// class:
/// - available: number of resources instances currently available;
/// - max: matrix of the maximum number of resources instances that each task
/// may require;
/// - alloc: matrix of current resources instances allocation of each task.
/// - need: matrix of current resources instances needs of each task.
/// Assume that these data structure are already filled with the
/// information described, in other words, you need to use these data structures
/// in read-only.
///
/// Suggestion!
/// From arr_math.h you may need only: arr_g_any(), arr_add(), arr_sub(),
/// all() and arr_ne();
#include "deadlock_prevention.h"
#include "arr_math.h"
#include "kheap.h"

/// Array of resources instances currently available;
uint32_t *  available;
/// Matrix of the maximum resources instances that each task may require;
uint32_t ** max;
/// Matrix of current resources instances allocation of each task.
uint32_t ** alloc;
/// Matrix of current resources instances need of each task.
uint32_t ** need;

/// @brief Check if the current system resource allocation maintains the system
/// in a safe state.
/// @param arr_available    Array of resources instances currently available.
/// @param mat_alloc        Matrix of current resources instances allocation of
///                         each task.
/// @param mat_need         Matrix of current resources instances need of each
///                         task.
/// @param n Number of tasks currently in the system.
/// @param m Number of resource types in the system (length of req_vec).
static bool_t state_safe(uint32_t *arr_available, uint32_t **mat_alloc,uint32_t **mat_need, size_t n, size_t m){
    // work è una copia di avaiable
    uint32_t *work = memcpy(kmalloc(sizeof(uint32_t) * m), available,sizeof(uint32_t) * m);

    // inizializzo gli array di modo che contengano tutti false
    uint32_t *finish = all(kmalloc(sizeof(uint32_t) * n), 0UL, n);
    uint32_t *all_true = all(kmalloc(sizeof(uint32_t) * n), 1UL, n);

    int i;

    // scorro finchè l'array non contiene tutti true
    while (arr_ne(finish,all_true,n)){
        // cerco un processo che possa soddisfare tutte le risorse di cui ha bisogno
        for (i = 0; i < n && (finish[i] || arr_g_any(need[i],work,m)); i++);
        if (i == n){
            kfree(work);
            kfree(finish);
            kfree(all_true);
            return false;
        }
        else{
            // faccio finta di rendere disponibili le risorse
           arr_add(work,alloc[i],m);
           finish[i]=1;
        }
    }

    // libero la memoria
    kfree(work);
    kfree(finish);
    kfree(all_true);
    return true;
}

deadlock_status_t request(uint32_t *req_vec, size_t task_i,uint32_t *arr_available, uint32_t ** mat_alloc, uint32_t **mat_need,size_t n, size_t m){
    available = arr_available;
    alloc = mat_alloc;
    need = mat_need;

    if (arr_g_any(req_vec,need[task_i],m))
        return ERROR;

    if (arr_g_any(req_vec,available,m))
        return WAIT;

    // provo ad allocare risorse
    arr_sub(available,req_vec,m);
    arr_add(alloc[task_i],req_vec,m);
    arr_sub(need[task_i],req_vec,m);

    // controllo di essere in uno stato safe
    if (!state_safe(available, alloc, need, n, m)){
        // torno all'allocazione precedente
        arr_add(available,req_vec,m);
        arr_sub(alloc[task_i],req_vec,m);
        arr_add(need[task_i],req_vec,m);
        return WAIT_UNSAFE;
    }
    return SAFE;
}
