int console_prefix(const string& errorText)
{
    int Hour = 0;
    int Min = 0;
    int Sec = 0;
    time_t timer = time(0);
    tm bt{};
#if UNIX
    time_t currentTime;
    struct tm* localTime;

    time(&currentTime); 
    localTime = localtime(&currentTime);

    Hour = localTime->tm_hour;
    Min = localTime->tm_min;
    Sec = localTime->tm_sec; #elif WINDOWS
    localtime_s(&bt, &timer);
    Hour = bt.tm_hour;
    Min = bt.tm_min;
    Sec = bt.tm_sec;
#else
    static mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    bt = *localtime(&timer);
#endif
    PrintColored("[" + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + "] ", blueFGColor, "", true);
    PrintColored("LOUI: ", yellowFGColor, "", true);
    PrintColored(escaped(errorText), redFGColor, "", true);
    cerr << std::endl;
    InterpreterLog("Press Enter to Exit...");
    cin.ignore();
    exit(1);
       cerr << "\x1B[34m[" + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + "] \x1B[33mLOUI: \x1B[31mERROR: " << errorText << "\033[0m\t\t" << endl;
exit(EXIT_FAILURE);
    return 2;
}
