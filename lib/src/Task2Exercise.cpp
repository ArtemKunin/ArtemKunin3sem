#include "Task2Exercise.h"

Task2Exercise::Task2Exercise(Matrix &src, Generator &gen) : Exercise(src, gen) {}

Matrix Task2Exercise::solve()
{
    const size_t rows = source.getRows();
    const size_t columns = source.getColumns();

    if (rows == 0 || columns == 0)
    {
        return Matrix();
    }
    int minValue = source[0][0];
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (source[i][j] < minValue)
            {
                minValue = source[i][j];
            }
        }
    }
    int *sequenceRow = new int[columns];
    for (size_t j = 0; j < columns; j++)
    {
        sequenceRow[j] = j + 1;
    }
    Matrix result(source);
    for (size_t i = result.getRows(); i > 0; --i)
    {
        size_t actual_index = i - 1;
        bool hasMin = false;

        for (size_t j = 0; j < columns; j++)
        {
            if (result[actual_index][j] == minValue)
            {
                hasMin = true;
                break;
            }
        }

        if (hasMin)
        {
            result.insertRowAfter(actual_index, sequenceRow);
        }
    }
    delete[] sequenceRow;

    return result;
}
