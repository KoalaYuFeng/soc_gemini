#include <stdio.h>
#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, data_send, data_recv;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("This example requires at least two processes.\n");
        MPI_Finalize();
        return 1;
    }

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;

    for (int i = 0; i < 10; i++) {
        if (rank == 0) {
            data_send = 42 + i;
            MPI_Send(&data_send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            printf("Process 0 sent data %d to Process 1.\n", data_send);

            MPI_Recv(&data_recv, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process 0 received data %d from Process 1.\n", data_recv);

            MPI_Get_processor_name(processor_name, &name_len);
            // std::cout << "Hello, world! I am process " << rank << std::endl;

            std::cout << "Hello, world! I am process " << rank << " out of " << size
                    << " processes running on node " << processor_name << std::endl;


        } else if (rank == 1) {
            MPI_Recv(&data_recv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process 1 received data %d from Process 0.\n", data_recv);

            data_send = data_recv + 1;
            MPI_Send(&data_send, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            printf("Process 1 sent data %d to Process 0.\n", data_send);

            MPI_Get_processor_name(processor_name, &name_len);
            // std::cout << "Hello, world! I am process " << rank << std::endl;

            std::cout << "Hello, world! I am process " << rank << " out of " << size
                    << " processes running on node " << processor_name << std::endl;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
