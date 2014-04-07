#include <stdio.h>
#include <vector>
#include <deque>

using std::vector;
using std::deque;

int enqueueAndGetMaximum(deque<int>* currentMaximums, int number)
{
    while (!currentMaximums->empty() && currentMaximums->back() < number)
    {
        currentMaximums->pop_back();
    }
    currentMaximums->push_back(number);
    return currentMaximums->front();
}

int dequeueAndGetMaximum(deque<int>* currentMaximums, int number)
{
    if (currentMaximums->front() == number)
    {
        currentMaximums->pop_front();
    }
    return currentMaximums->front();
}

vector<int> maximums(vector<int> numbers, vector<char> shifts)
{
    deque<int> currentMaximums;
    vector<int> maximums;
    size_t firstIndex = 1;
    size_t lastIndex = 0;
    currentMaximums.push_back(numbers[0]);

    for (size_t index = 0; index < shifts.size(); ++index)
    {
        char shift = shifts[index];
        int maximum;
        if (shift == 'R')
        {
            maximum = enqueueAndGetMaximum(&currentMaximums, numbers[firstIndex++]);
        }
        else if (shift == 'L')
        {
            maximum = dequeueAndGetMaximum(&currentMaximums, numbers[lastIndex++]);
        }
        maximums.push_back(maximum);                    
    }
    return maximums;
}

vector<int> input_numbers()
{
    int numberOfNumbers;
    vector<int> input;
    scanf("%d", &numberOfNumbers);
    for (int i = 0; i < numberOfNumbers; ++i)
    {
        int num = 0;
        scanf("%d", &num);
        input.push_back(num);
    }
    return input;
}

vector<char> inputShifts()
{
    int numberOfShifts;
    vector<char> input;
    scanf("%d", &numberOfShifts);
    scanf("\n");
    if (numberOfShifts < 1)
    {
        return input;
    }
    char c = 0;
    for (int i = 0; i < numberOfShifts - 1 ; ++i)
    {
        scanf("%c ", &c);
        input.push_back(c);
    }
    scanf("%c", &c);
    input.push_back(c);
    return input;
}

int main()
{
    vector<int> numbers = input_numbers();
    vector<char> shifts = inputShifts();
    vector<int> maxs = maximums(numbers, shifts);
    for (size_t i = 0; i < maxs.size(); ++i)
    {
        printf("%d ", maxs[i]);
    }
    return 0;
}