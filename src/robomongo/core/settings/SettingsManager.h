#pragma once

#include <QString>
#include <QVariantMap>
#include <vector>
#include "robomongo/core/Enums.h"

namespace Robomongo
{
    class ConnectionSettings;
    /**
     * @brief SettingsManager gives you access to all settings, that is used
     *        by Robomongo. It can load() and save() them. Config file usually
     *        located here: ~/.config/robomongo/robomongo.json
     *
     *        You can access this manager via:
     *        AppRegistry::instance().settingsManager()
     *
     * @threadsafe no
     */
    class SettingsManager
    {
    public:
        typedef std::vector<ConnectionSettings *> ConnectionSettingsContainerType;
        typedef QMap<QString, QVariant> ToolbarSettingsContainerType;
        /**
         * @brief Creates SettingsManager for config file in default location
         *        (usually ~/.config/robomongo/robomongo.json)
         */
        SettingsManager();

        /**
         * @brief Cleanup owned objects
         */
        ~SettingsManager();

        /**
         * @brief Load settings from config file.
         * @return true if success, false otherwise
         */
        bool load();

        /**
         * @brief Saves all settings to config file.
         * @return true if success, false otherwise
         */
        bool save();

        /**
         * @brief Adds connection to the end of list.
         * Connection now will be owned by SettingsManager.
         */
        void addConnection(ConnectionSettings *connection);

        /**
         * @brief Removes connection by index
         */
        void removeConnection(ConnectionSettings *connection);

        /**
        * @brief Finds and returns original (non-clone) connection settings.
        * @param uniqueID : Unique ID for an original (non-clone) connection settings.
        * @return If uniqueID is valid returns original (non-clone) connection settings, 
        *         nullptr otherwise.
        */
        ConnectionSettings* getConnectionSettings(int uniqueId);

        void reorderConnections(const ConnectionSettingsContainerType &connections);

        void setToolbarSettings(QString toolbarName, bool visible);

        /**
         * @brief Returns list of connections
         */
        ConnectionSettingsContainerType connections() const { return _connections; }

        ToolbarSettingsContainerType toolbars() const { return _toolbars; }

        void setUuidEncoding(UUIDEncoding encoding) { _uuidEncoding = encoding; }
        UUIDEncoding uuidEncoding() const { return _uuidEncoding; }

        void setTimeZone(SupportedTimes timeZ) { _timeZone = timeZ; }
        SupportedTimes timeZone() const { return _timeZone; }

        void setViewMode(ViewMode viewMode) { _viewMode = viewMode; }
        ViewMode viewMode() const { return _viewMode; }

        void setAutocompletionMode(AutocompletionMode mode) { _autocompletionMode = mode; }
        AutocompletionMode autocompletionMode() const { return _autocompletionMode; }

        void setAutoExpand(bool isExpand) { _autoExpand = isExpand; }
        bool autoExpand() const { return _autoExpand; }

        void setAutoExec(bool isAutoExec) { _autoExec = isAutoExec; }
        bool autoExec() const { return _autoExec; }

        void setMinimizeToTray(bool isMinimizingToTray) { _minimizeToTray = isMinimizingToTray; }
        bool minimizeToTray() const { return _minimizeToTray; }

        void setLineNumbers(bool showLineNumbers) { _lineNumbers = showLineNumbers; }
        bool lineNumbers() const { return _lineNumbers; }

        void setLoadMongoRcJs(bool isLoadJs) { _loadMongoRcJs = isLoadJs; }
        bool loadMongoRcJs() const { return _loadMongoRcJs; }

        void setDisableConnectionShortcuts(bool isDisable) { _disableConnectionShortcuts = isDisable; }
        bool disableConnectionShortcuts() const { return _disableConnectionShortcuts; }

        void setBatchSize(int batchSize) { _batchSize = batchSize; }
        int batchSize() const { return _batchSize; }

        QString currentStyle() const { return _currentStyle; }
        void setCurrentStyle(const QString& style);

        QString textFontFamily() const { return _textFontFamily; }
        void setTextFontFamily(const QString& fontFamily);

        int textFontPointSize() const { return _textFontPointSize; }
        void setTextFontPointSize(int pointSize);

        int mongoTimeoutSec() const { return _mongoTimeoutSec; }
        int shellTimeoutSec() const { return _shellTimeoutSec; }

        // True when settings from previous versions of
        // Robomongo are imported
        void setImported(bool imported) { _imported = imported; }
        bool imported() const { return _imported; }

        /**
         * Returns number of imported connections
         */
        int importedConnectionsCount();

    private:

        /**
         * Load settings from the map. Existing settings will be overwritten.
         */
        void loadFromMap(QVariantMap &map);

        /**
         * Save all settings to map.
         */
        QVariantMap convertToMap() const;

        /**
         * Load connection settings from previous versions of Robomongo
         */
        void importConnections();
        void importConnectionsFrom_0_8_5_to_0_9();
        void importConnectionsFrom_0_9_to_1_0();

        /**
         * @brief Version of settings schema currently loaded
         */
        QString _version;

        UUIDEncoding _uuidEncoding;
        SupportedTimes _timeZone;
        ViewMode _viewMode;
        AutocompletionMode _autocompletionMode;
        bool _loadMongoRcJs;
        bool _autoExpand;
        bool _autoExec;
        bool _minimizeToTray;
        bool _lineNumbers;
        bool _disableConnectionShortcuts;
        int _batchSize;
        QString _currentStyle;
        QString _textFontFamily;
        int _textFontPointSize;

        int _mongoTimeoutSec;
        int _shellTimeoutSec;

        // True when settings from previous versions of
        // Robomongo are imported
        bool _imported;

        /**
         * @brief List of connections
         */
        ConnectionSettingsContainerType _connections;
        ToolbarSettingsContainerType _toolbars;

        // Unique Id counter which is incremented only when a non-clone ConnectionSettings 
        // object is created and assigned can be assigned to clone or non-clone 
        // ConnectionSettings objects in order to identify source object ID for a clone.
        static int _uniqueIdCounter;
    };
}
