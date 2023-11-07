#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    // std::cout << "Hello, world! I am process " << rank << std::endl;

    std::cout << "Hello, world! I am process " << rank << " out of " << size
              << " processes running on node " << processor_name << std::endl;

    MPI_Finalize();
    return 0;
}
