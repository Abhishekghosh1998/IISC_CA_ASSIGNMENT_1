Requirements:
    python 3.x
    matplotlib - library for graph rendering using python

Installation:
    1) install python - https://www.python.org/downloads/
    2) pip install matplotlib

Directory Setup:
    Creat a folder called "graphs" in the path where the python file - genGraphNewFormat.py is present.
    This folder will serve as the output folder where the generated graphs will be stored after execution of the python program.
Command to Run :
    py genGraphNewFormat.py <path_of_the_directory_containing_the_log_files>
    path_of_the_directory_containing_the_log_files => The directory should contain log files in the format as follows:
        stat_matrixOrder_tileSize_loopOrdering.log
        Example:
            stat_2048_8_i_j_k.log
    Example:
        py genGraphNewFormat.py "C:\Users\Kanmani A\Documents\Computer_Arch\Question_1_outputs\8192_outputs"

Output: 
    The matplotlib graph rendering window opens.
    Graphs show up one after the other, once you close the window of the current graph, the next graph window is displayed.
    The graph can be zoomed in, axes of the graph can also be zoomed in the matplotlib graph rendering window.
    After the program renders all the graphs and finishes execution, the output graphs are stored in the "./graphs" folder that was created in the Directory Setup phase.