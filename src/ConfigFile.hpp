#ifndef CONFIG_FILE_HPP
#define CONFIG_FILE_HPP

class ConfigFile
{
public:
    ConfigFile() = default;

    void load();
    void save();

    void setWidth(int val);
    void setHeight(int val);
    void setFullscreen(bool val);
    void setMusic(bool val);
    void setDifficulty(int val);

    int  getWidth() const;
    int  getHeight() const;
    bool isFullscreen() const;
    bool isMusic() const;
    int  getDifficulty() const;

private:
    int  Width;
    int  Height;
    bool Fullscreen;
    bool Music;
    int  Difficulty ;

    int  NumMonitors = 1;
};

extern ConfigFile GlobalConfigFile;

#endif
