#ifndef SHELL_LAN_CONFIG_SERIALIZER_H
#define SHELL_LAN_CONFIG_SERIALIZER_H

#include <FeShell/Export.h>
#include <FeUtils/tinyXml/tinyxml.h>
#include <FeUtils/tinyXml/tinyutil.h>

#include <string>
#include <map>

namespace FeShell
{
    /**
    * @class CLanConfigModule
    * @brief 系统语言配置文件模型
    * @note 定义了系统语言配置文件的模型，保存和系统语言配置文件的数据信息和获取数据信息的接口
    * @author c00005
    */
    class FESHELL_EXPORT CLanConfig
	{
	public:
		//语言的Key以及对应的语言解析文件的文件名 
		typedef std::map<std::string, std::string> LanMap;

    public:
        CLanConfig();
        ~CLanConfig();

    public:
		bool Valid();
		void SetValid(bool bValue);

		void SetLanguageList(std::string strKey, std::string strValue);
		LanMap GetLanguageList();

		std::string GetDefLanguage();
		void SetDefLanguage(std::string strLan);

	private:
		bool                        m_bValid;           //是否合法

		std::string					m_strDefLan;
		LanMap						m_mapLan;
    };
}

namespace FeShell
{
    /**
      * @class CLanConfigReader
      * @brief 语言配置的序列化器
      * @note 序列化系统语言配置的信息，从语言配置文件中获得系统所需要的语言信息
      * @author c00005
    */
    class FESHELL_EXPORT CLanConfigReader :public FeUtil::TiXmlVisitor
    {
    public:
        CLanConfigReader();
        ~CLanConfigReader();

		///获得指定的配置文件配置信息
        CLanConfig Execute(const std::string& strFileName);

		///获得默认的配置文件下的配置信息
		CLanConfig ExecuteDefault();

    public:
        virtual bool VisitEnter(const FeUtil::TiXmlElement& ele , const FeUtil::TiXmlAttribute* attr);

    protected:
        bool AcceptLan(const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr);

    protected:
        CLanConfig      m_configModule; //系统语言配置数据模型
    };

	/**
      * @class CLanConfigReader
      * @brief 语言配置的序列化器
      * @note 序列化系统语言配置的信息，从语言配置文件中获得系统所需要的语言信息
      * @author c00005
    */
	class FESHELL_EXPORT CLanConfigWriter : public FeUtil::TiXmlVisitor
	{
	public:
		CLanConfigWriter();

		virtual ~CLanConfigWriter();

	public:
		bool Execute(CLanConfig pLanConfig);

		bool Execute(CLanConfig pLanConfig, const std::string& strFileName);

	};
}

#endif//SHELL_LAN_CONFIG_SERIALIZER_H
