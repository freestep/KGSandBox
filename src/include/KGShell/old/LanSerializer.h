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
    * @brief ϵͳ���������ļ�ģ��
    * @note ������ϵͳ���������ļ���ģ�ͣ������ϵͳ���������ļ���������Ϣ�ͻ�ȡ������Ϣ�Ľӿ�
    * @author c00005
    */
    class FESHELL_EXPORT CLanConfig
	{
	public:
		//���Ե�Key�Լ���Ӧ�����Խ����ļ����ļ��� 
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
		bool                        m_bValid;           //�Ƿ�Ϸ�

		std::string					m_strDefLan;
		LanMap						m_mapLan;
    };
}

namespace FeShell
{
    /**
      * @class CLanConfigReader
      * @brief �������õ����л���
      * @note ���л�ϵͳ�������õ���Ϣ�������������ļ��л��ϵͳ����Ҫ��������Ϣ
      * @author c00005
    */
    class FESHELL_EXPORT CLanConfigReader :public FeUtil::TiXmlVisitor
    {
    public:
        CLanConfigReader();
        ~CLanConfigReader();

		///���ָ���������ļ�������Ϣ
        CLanConfig Execute(const std::string& strFileName);

		///���Ĭ�ϵ������ļ��µ�������Ϣ
		CLanConfig ExecuteDefault();

    public:
        virtual bool VisitEnter(const FeUtil::TiXmlElement& ele , const FeUtil::TiXmlAttribute* attr);

    protected:
        bool AcceptLan(const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr);

    protected:
        CLanConfig      m_configModule; //ϵͳ������������ģ��
    };

	/**
      * @class CLanConfigReader
      * @brief �������õ����л���
      * @note ���л�ϵͳ�������õ���Ϣ�������������ļ��л��ϵͳ����Ҫ��������Ϣ
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
