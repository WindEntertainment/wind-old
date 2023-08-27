#include "logger.h"

namespace app {
    _Logger::Logger* logger() {
        static _Logger::Logger* instance = new _Logger::Logger([](_Logger::LoggerInitSettings* self) {
            self->name = "logger";
            self->path_to_save = "./logs/";
            self->enable_console_output = true;
            self->enable_file_output = true;
            self->num_space_for_section = 3;
        });
        return instance;
    }

    //===================================================================//

    fs::directory_entry getOldestFileInDirectory(fs::path directory) {
        fs::directory_entry oldest_file;
        for (auto file : fs::directory_iterator(directory)) {
            auto write_time = fs::last_write_time(file); 
            if (!oldest_file.exists() || write_time < fs::last_write_time(oldest_file))
                oldest_file = file;
        }
        return oldest_file;
    }

    size_t numberOfFilesInDirectory(fs::path path) {
        using std::filesystem::directory_iterator;
        return std::distance(directory_iterator(path), directory_iterator{});
    }

    string getPathForLogFile(string path_to_save, string logger_name, string time_info) {
        return path_to_save + logger_name + ": " + time_info;
    }

    //===================================================================//

    namespace _Logger {
        void Logger::file_output_init() {
            
            //
            if (!fs::exists(settings->path_to_save)) {
                this->error() << "couldn't open folder for save logs:" << settings->path_to_save;
                return;
            }

            // if num files in directory more than 10 remove oldest log file
            size_t num_files = numberOfFilesInDirectory(settings->path_to_save);
            if (num_files >= 10) 
                remove(getOldestFileInDirectory(settings->path_to_save));


            // generate name for new log file. format: [logger-name]: [date]
            string path = getPathForLogFile(
                settings->path_to_save, settings->name,
                string(asctime(&m_time_info))
            ); 

            // trying open file
            m_file.open(path);
            if (!m_file.is_open())
                this->error() << "file for save log doesn't exist:" << path;

        }
        
        //
        void Logger::close() {
            this->info() << "Closed logger with name " + settings->name;
            if (m_file.is_open())
                m_file.close();
        }

        //
        Logger::Logger(void (*config)(LoggerInitSettings*)) {
            settings = new LoggerInitSettings();
            config(settings);
            
            time_t t = time(NULL);
            this->m_time_info = *localtime(&t);
            this->m_num_section = 0;

            if (settings->enable_file_output)
                file_output_init();
            
            this->info() << "logger started";
        }  
    }
}