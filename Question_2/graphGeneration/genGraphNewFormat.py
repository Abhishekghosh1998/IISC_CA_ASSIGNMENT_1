import os
import sys
import matplotlib.pyplot as plt
from matplotlib.gridspec import GridSpec

def windowSizeBasedSorting(fileName):
    return int(fileName.split('_')[2])

path_arg_index=1
path = sys.argv[path_arg_index]
#"C://Users//Kanmani A//Documents//Computer_Arch//outputs"
dir_list = os.listdir(path) 
print(dir_list)

dir_list.sort(key=windowSizeBasedSorting)

measureDict={
    'L1-dcache-load-misses':[], 
    'L1-icache-load-misses':[],
    'LLC-load-misses':[], 
    'LLC-store-misses':[], 
    'dTLB-load-misses':[], 
    'dTLB-store-misses':[], 
    'iTLB-load-misses':[], 
    'cache-misses':[], 
    'page-faults':[],
    'time-elapsed':[]
}


fileMissesCount=[]
mostMinMisses=[]

for i in range(len(dir_list)):
    fileMissesCount.append(0)
    mostMinMisses.append(0)

currentFile=0

for fileName in dir_list:
    f = open(path+'/'+fileName,'r')
    count=0
    for row in f:
        count=count+1
        if("time" not in row):
            row = row.split('=')
            if(len(row)>=2):
                row[0]=row[0].strip()
                row[1]=row[1].strip()
                if(row[0].strip() in measureDict.keys()):
                    val=int(row[1])
                    measureDict[row[0]].append(val)
                    fileMissesCount[currentFile]=fileMissesCount[currentFile]+val
        elif("time elapsed" in row):
            row = row.split('=')
            if(len(row)>=2):
                measureDict['time-elapsed'].append(float(row[1].strip()))

    currentFile=currentFile+1

print(measureDict)

print('Total missCounts respectively :')
print(fileMissesCount)

for fileIndex in range(len(dir_list)):
    stringToReplace=dir_list[fileIndex][:10]
    dir_list[fileIndex]=dir_list[fileIndex].replace(stringToReplace,'')
    dir_list[fileIndex]=dir_list[fileIndex].replace('.log','')

barColors=('#084f0e','#084f0e','#084f0e',
            '#c45e62','#c45e62','#c45e62',
            '#032b6b','#032b6b','#032b6b',
            '#5b615c','#5b615c','#5b615c',
            '#d17f0d','#d17f0d','#d17f0d',
            '#4f2e61','#4f2e61','#4f2e61',
            '#0b4147','#0b4147','#0b4147',
            '#8a8f0a','#8a8f0a','#8a8f0a',
            '#5c3516','#5c3516','#5c3516',
            )
max_y_lim = max(fileMissesCount) + .15*max(fileMissesCount)
min_y_lim = min(fileMissesCount)
plt.ylim(min_y_lim, max_y_lim)
plottedGraph=plt.bar(dir_list,fileMissesCount, color = barColors)
plt.bar_label(plottedGraph,fmt="%.2g",fontsize=6, rotation=90, padding=2)
plt.xlabel('Methods', fontsize = 12)
plt.ylabel('Total Misses Count', fontsize = 12)
plt.title('Total Misses of Each Method', fontsize = 20)
plt.xticks(rotation=90)
plt.legend()
plt.savefig('graphs/totalMisses',bbox_inches='tight')
plt.show()


for measure in measureDict:
    if(measure=='time-elapsed'):
        max_y_lim = max(measureDict[measure]) + .15*max(measureDict[measure])
        min_y_lim = min(measureDict[measure])
        plt.ylim(min_y_lim, max_y_lim)
        plottedGraph=plt.bar(dir_list,measureDict[measure], color = barColors)
        plt.bar_label(plottedGraph,fmt="%.2g",fontsize=6, rotation=90, padding=2)
        plt.xlabel('Different Implementations', fontsize = 12)
        plt.ylabel('Time Elapsed in seconds', fontsize = 12)
        plt.title(' Graph for Time Elapsed', fontsize = 20)
        plt.xticks(rotation=90)
        plt.legend()
        plt.savefig('graphs/'+measure,bbox_inches='tight')
        plt.show()
    else:
        max_y_lim = max(measureDict[measure]) + .15*max(measureDict[measure])
        min_y_lim = min(measureDict[measure])
        plt.ylim(min_y_lim, max_y_lim)
        plottedGraph=plt.bar(dir_list,measureDict[measure], color = barColors)
        plt.bar_label(plottedGraph,fmt="%.2g",fontsize=6, rotation=90, padding=2)
        plt.xlabel('Different Implementations', fontsize = 12)
        plt.ylabel('Misses_Count', fontsize = 12)
        plt.title('Graph for '+measure, fontsize = 20)
        plt.xticks(rotation=90)
        plt.legend()
        plt.savefig('graphs/'+measure,bbox_inches='tight')
        plt.show()
        minMissIndex=measureDict[measure].index(min(measureDict[measure]))
        mostMinMisses[minMissIndex]=mostMinMisses[minMissIndex]+1

minMissLabels=[]
minMissCounts=[]
for i in range(len(mostMinMisses)):
    if(mostMinMisses[i]!=0):
        minMissCounts.append(mostMinMisses[i])
        minMissLabels.append(dir_list[i])

print(minMissCounts)
fig1, ax1 = plt.subplots()
ax1.pie(minMissCounts, labels=minMissLabels, autopct='%1.1f%%',
        shadow=True, startangle=90)
ax1.axis('equal')
plt.title('Piechart showing the percentage of the frequency \nof the best combination (tile size and loop orderings) \nin each performance measurement\n', fontsize = 14) 
plt.savefig('graphs/minMisses',bbox_inches='tight')
plt.show()