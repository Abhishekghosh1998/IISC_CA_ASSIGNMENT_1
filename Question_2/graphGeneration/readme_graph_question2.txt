Requirements:
    python 3.x
    matplotlib - library for graph rendering using python

Installation:
    1) install python - https://www.python.org/downloads/
    2) pip install matplotlib

Directory Setup:
    Creat a folder called "graphsDram" in the path where the python file - genGraphNewFormat.py is present.
    This folder will serve as the output folder where the generated graphs will be stored after execution of the python program.
Command to Run :
    py genGraphDram.py <path_of_the_directory_containing_the_log_files>
    path_of_the_directory_containing_the_log_files => The directory should contain log files in the format as follows:
        <OPEN/CLOSE>_<CACHE/ROW>_<FCFS/FRFCFS>.txt
        Example:
            OPEN_CACHE_FCFS.txt
            
    Example:
        py genGraphDram.py "C:\Users\Kanmani A\Documents\Computer_Arch\DRAMSim_outputs\bench3_outputs"
Output: 
    The matplotlib graph rendering window opens.
    Graphs show up one after the other, once you close the window of the current graph, the next graph window is displayed.
    The graph can be zoomed in, axes of the graph can also be zoomed in the matplotlib graph rendering window.
    After the program renders all the graphs and finishes execution, the output graphs are stored in the "./graphsDram" folder that was created in the Directory Setup phase.