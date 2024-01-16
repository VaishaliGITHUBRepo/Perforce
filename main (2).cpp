#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

struct VisitorEvent{
    int time;
    int enter; // 1 for entering, -1 for leaving
};

//Function to parse time in HH:MM format and convert it to minutes
int parseTime(const std::string& time){
    int hours,minutes;
    char colon;
    std::istringstream ss(time);
    ss >> hours >> colon >> minutes;
    return hours * 60 + minutes;
}

//Function to find the time period with the most visitors
std::pair<std::pair<int, int>, int> findMostVisitors(const vector<std::pair<int, int> >& timePairs){
    std::map<int,int>visitorCount; //Map to store count of visitors at each minute
    
	for(const auto& pair : timePairs){ 
        for (int i = pair.first; i <= pair.second; ++i) {
            visitorCount[i]++;
        }
    }

	 auto maxCount = std::max_element(visitorCount.begin(), visitorCount.end(),
        [](const auto& p1, const auto& p2) { return p1.second < p2.second; });
		
	int startTime = maxCount->first;
    int endTime = startTime;

    // Find the end time corresponding to the start time
	for (int i = startTime + 1; visitorCount[i] == maxCount->second; ++i)
	{
            endTime = i;
    }
    
    return std::make_pair(
        std::make_pair(startTime, endTime),
        maxCount->second
    );


}

int main(int argc,char* argv[]){
    if(argc !=2){
        std::cerr << "Usage: "<<argv[0] << " <input_file_path>" <<endl;
        return 1;
    }

    //Read visiting times from the input file
    std::ifstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        std::cerr << "Error opening file: " << argv[1] <<endl;
        return 1;
    }

    std::vector<std::pair<int, int> >timePairs;

    string line;
    while(getline(inputFile,line)){
        std::istringstream ss(line);
        std::string enterTime,leaveTime;
        std::getline(ss,enterTime,',');
        std::getline(ss,leaveTime,',');
        int enterMinutes = parseTime(enterTime);
        int leaveMinutes = parseTime(leaveTime);
        timePairs.emplace_back(enterMinutes,leaveMinutes);
    }

    //Find the time period with the most visitors
    auto result = findMostVisitors(timePairs);

    //Output the result
    cout<< result.first.first / 60 << ":" <<result.first.first%60<<"-"<<result.first.second/60 << ":"<<result.first.second%60<<";"<<result.second<<endl;

    return 0;

}
