#ifndef SHELL_SYSTEM_CONFIG_SERIALIZER_H
#define SHELL_SYSTEM_CONFIG_SERIALIZER_H

#include <osgEarth/Viewpoint>

#include <FeUtils/tinyXml/tinyxml.h>
#include <FeUtils/tinyXml/tinyutil.h>

#include <FeUtils/FreeViewPoint.h>
#include <FeShell/Export.h>

namespace FeShell
{
    /**
    * @class CSysConfigModule
    * @brief 系统配置文件模型
    * @note 定义了系统配置文件的模型，保存和系统配置文件的数据信息和获取数据信息的接口
    * @author l00008
    */
    class FESHELL_EXPORT CSysConfig
    {
    public:
        CSysConfig();
        ~CSysConfig();

    public:
        std::string GetSystemTitle() const;
        void SetSystemTitle(const std::string& strValue);

        std::string GetSystemIcon() const;
        void SetSystemIcon(const std::string& strValue);

        std::string GetEarthFile() const;
        void SetEarthFile(const std::string& strValue);

		std::string GetFeatureLayerConfig() const;
		void SetFeatureLayerConfig(const std::string& strValue);

		std::string GetMarksConfig() const;
		void SetMarksConfig(const std::string& strValue);

        FeUtil::CFreeViewPoint GetBeginViewPoint() const;
        void SetBeginViewPoint(const FeUtil::CFreeViewPoint& sValue);

		FeUtil::CFreeViewPoint GetEndViewPoint() const;
		void SetEndViewPoint(const FeUtil::CFreeViewPoint& sValue);

		std::string GetCustomLayerConfig() const;
		void SetCustomLayerConfig(const std::string& strValue);

		std::string GetContourConfig() const;
		void SetContourConfig(const std::string& strValue);

    private:
		std::string                m_strEarthPath;			//解析到的地球文件路径
        std::string                m_strSystemTitle;		//解析到的系统名称
		std::string                m_strSystemIcon;			//解析系统的图标路径
		std::string                m_strFeatureLayerConfig; //矢量配置
		std::string                m_strCustomLayerConfig;  //用户自定义图层配置
		std::string                m_strMarksConfig;		//国际化环境配置文件
		std::string                m_strContourConfig;		//眩晕图的默认配色方案
        FeUtil::CFreeViewPoint     m_sViewPointBegin;       //视点封装体
		FeUtil::CFreeViewPoint     m_sViewPointEnd;			//视点封装体
    };
}

namespace FeShell
{
    /**
      * @class CSystemConfigLoader
      * @brief 系统配置的序列化器
      * @note 序列化系统配置的信息，从配置文件中获得系统所需要的信息
      * @author l00008
    */
    class FESHELL_EXPORT CSystemConfigLoader :public FeUtil::TiXmlVisitor
    {
    public:
        CSystemConfigLoader();
        ~CSystemConfigLoader();

		///获得指定的配置文件配置信息
        bool Execute(const std::string& strFileName, CSysConfig& systemConfig);

		///获得默认的配置文件下的配置信息
		bool ExecuteDefault(CSysConfig& systemConfig);

    public:
        virtual bool VisitEnter(const FeUtil::TiXmlElement& ele , const FeUtil::TiXmlAttribute* attr);

    protected:
        bool AcceptCommon(const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr);

		bool AcceptViewPoint(const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr);

		void BuildViewPoint(const FeUtil::TiXmlElement* pElement, FeUtil::CFreeViewPoint& viewPoint);

    protected:
        CSysConfig      m_configModule; //系统配置数据模型
    };
}

#endif//SHELL_SYSTEM_CONFIG_SERIALIZER_H
