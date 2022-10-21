import matplotlib.pyplot as plt
import os
import sys
 
path_arg_index=1
path = sys.argv[path_arg_index]
#"C://Users//Kanmani A//Documents//Computer_Arch//outputs"
dir_list = os.listdir(path) 
print(dir_list)

dir_list=list(filter(lambda x: '.txt' in x, dir_list))

directMeasureDict={
    'average_bandwidth':[], 
    'num_write_row_hits':[],
    'num_read_row_hits':[],
    'all_bank_idle_cycles.0':[],
    'all_bank_idle_cycles.1':[],
    'num_cycles':[],
    'num_writes_done':[],
    'num_reads_done':[],
    'average_write_latency':[],
    'average_read_latency':[]
}

requiredMeasureDict={
    'average_bandwidth':[], 
    'row_hit_rate':[],
    'write_row_hit_rate':[],
    'read_row_hit_rate':[],
    'bank_level_parallelism':[], 
    'average_memory_access_time':[],
}

#currentFile=0

for fileName in dir_list:
    f = open(path+'/'+fileName,'r')
    count=0
    for row in f:
        count=count+1
        if(count>=3):
            row = row.split('=')
            if(len(row)>=2):
                row[0]=row[0].strip()  
                if(row[0] in directMeasureDict.keys()):
                    val=float(row[1].split('#')[0].strip())
                    directMeasureDict[row[0]].append(val)
    #currentFile=currentFile+1

requiredMeasureDict['average_bandwidth']=directMeasureDict['average_bandwidth']

for fileIndex in range(len(dir_list)):
    write_hit_rate_cur=float(directMeasureDict['num_write_row_hits'][fileIndex]/directMeasureDict['num_writes_done'][fileIndex])
    read_hit_rate_cur=float(directMeasureDict['num_read_row_hits'][fileIndex]/directMeasureDict['num_reads_done'][fileIndex])
    requiredMeasureDict['write_row_hit_rate'].append(write_hit_rate_cur)
    requiredMeasureDict['read_row_hit_rate'].append(read_hit_rate_cur)
    requiredMeasureDict['row_hit_rate'].append((write_hit_rate_cur+read_hit_rate_cur)/2)
    bank_idle_cycles=(directMeasureDict['all_bank_idle_cycles.0'][fileIndex]+directMeasureDict['all_bank_idle_cycles.1'][fileIndex])/2
    idle_total_cycles_ratio=float(bank_idle_cycles/directMeasureDict['num_cycles'][fileIndex])
    requiredMeasureDict['bank_level_parallelism'].append((1-idle_total_cycles_ratio))
    requiredMeasureDict['average_memory_access_time'].append(float((directMeasureDict['average_write_latency'][fileIndex]
    +directMeasureDict['average_read_latency'][fileIndex])/2))

for fileIndex in range(len(dir_list)):
    dir_list[fileIndex]=dir_list[fileIndex].replace('.txt','')

print(directMeasureDict)

print(requiredMeasureDict)

barColors=('#084f0e','#3a693d',
            '#783436','#c45e62',
            '#032b6b','#3e577d',
            '#5b615c','#838a84',
            '#d17f0d','#b89769',
            '#4f2e61','#846c91',
            )

for measure in requiredMeasureDict:
    if(len(dir_list)==len(requiredMeasureDict[measure])):
        max_y_lim = max(requiredMeasureDict[measure]) + .15*max(requiredMeasureDict[measure])
        plt.ylim(0, max_y_lim)
        plottedGraph=plt.bar(dir_list,requiredMeasureDict[measure],
        color = barColors)
        plt.bar_label(plottedGraph,fmt="%.3g",fontsize=6, rotation=90, padding=2)
        plt.xlabel('Different Implementations', fontsize = 12)
        plt.ylabel(measure, fontsize = 12)
        plt.xticks(rotation=90)
        plt.legend()
        plt.savefig('graphsDram/'+measure,bbox_inches='tight')
        plt.show()