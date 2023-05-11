#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int selectSort(int* nums, int left, int right){
    int minNum;
    int times = 0;
    int mid;
    for (int i = left; i <= right; i++){
        minNum = nums[i];
        mid = i;
        for (int j = i + 1; j <= right; j++){
            if (nums[j] < minNum){
                minNum = nums[j];
                mid = j;
            }
            times++;
        }
        swap(&nums[i], &nums[mid]);
    }
    return times;
}
int bubbleSort(int* nums, int left, int right){
    int times = 0;
    bool flag = false;
    for (int i = left; i < right; i++){
        flag = false;
        for (int j = left; j < right - i; j++){
            times++;
            if (nums[j + 1] < nums[j]){
                swap(&nums[j + 1], &nums[j]);
                flag = true;
            }
        }
        if (!flag){
            return times;
        }
    }
    return times;
}
int minHeapify(int* nums, int start, int end){
    int root = start;
    int child = 2 * root + 1;
    int times = 0;
    while (child <= end){
        if (child + 1 <= end && nums[child] < nums[child + 1]){
            child++;
        }
        times++;
        if (nums[child] < nums[root]){
            return times;
        }
        swap(&nums[child], &nums[root]);
        root = child;
        child = 2 * root + 1;
    }
    return times;
}
int heapSort(int* nums, int left, int right){
    int times = 0;
    for (int i = (left + right) / 2; i >= 0; i--){
        times += minHeapify(nums, i, right);
    }
    for (int i = right; i > 0; i--){
        swap(&nums[0], &nums[i]);
        times += minHeapify(nums, 0, i - 1);
    }
    return times;
}
int merge(int* source, int* temp, int leftA, int rightA, int leftB, int rightB){
    int i = leftA;
    int j = leftB;
    int k = leftA;
    int times = 0;
    while (i <= rightA && j <= rightB){
        times++;
        if (source[i] < source[j]) temp[k++] = source[i++];
        else temp[k++] = source[j++];
    }
    while (i <= rightA){
        temp[k++] = source[i++];
    }
    while (j <= rightB){
        temp[k++] = source[j++];
    }
    for (int m = leftA; m <= rightB; m++){
        source[m] = temp[m];
    }
    return times;
}
int mergeSort(int* nums, int left, int right, int* temp){
    int mid = (right + left) / 2;
    int times = 0;
    if (left < right){
        times += mergeSort(nums, left, mid, temp);
        times += mergeSort(nums, mid + 1, right, temp);
        times += merge(nums, temp, left, mid, mid + 1, right);
    }
    return times;
}
int quickSort(int* nums, int left, int right){
    if (left >= right){
        return 0;
    }
    int mid = nums[left];
    int i = left + 1;
    int j = right;
    int times = 0;
    while (i < j){
        while (i < j && nums[j] > mid){
            j--;
            times++;
        }
        if (i < j) times++;
        while (i < j && nums[i] < mid){
            i++;
            times++;
        }
        if (i < j) times++;
        if (i < j) swap(&nums[i], &nums[j]);
    }
    if (nums[i] < nums[left]){
        swap(&nums[left], &nums[i]);
        times += quickSort(nums, left, i - 1);
        times += quickSort(nums, i + 1, right);
    }
    else{
        times += quickSort(nums, left + 1, right);
    }
    return times;
}
/* this function can sort the array correctly */
/* but the times is incorrect */
/* maybe is not the standard algorithm of quick sort */
int QSort(int* nums, int left, int right){
    int i, last;
    int times = 0;
    if (left < right){
        last = left;
        for (i = left + 1; i <= right; i++){
            times++;
            if (nums[i] < nums[left]){
                swap(&nums[++last], &nums[i]);
            }
        }
        swap(&nums[left], &nums[last]);
        times += QSort(nums, left, last - 1);
        times += QSort(nums, last + 1, right);
    }
    return times;
}
int main(){
    int length;
    int category;
    scanf("%d %d", &length, &category);
    int numbers[100];
    for (int i = 0; i < length; i++){
        scanf("%d", numbers + i);
    }
    int ans = 0;
    if (category == 1){
        ans = selectSort(numbers, 0, length - 1);
    }
    else if (category == 2){
        ans = bubbleSort(numbers, 0, length - 1);
    }
    else if (category == 3){
        ans = heapSort(numbers, 0, length - 1);
    }
    else if (category == 4){
        int* arr = malloc(length * sizeof(int));
        ans = mergeSort(numbers, 0, length - 1, arr);
        free(arr);
    }
    else if (category == 5){
        ans = QSort(numbers, 0, length - 1);
    }
    for (int i = 0; i < length; i++){
        printf("%d ", numbers[i]);
    }
    printf("\n%d", ans);
    return 0;
}