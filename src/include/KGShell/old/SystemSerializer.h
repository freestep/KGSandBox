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
    * @brief ϵͳ�����ļ�ģ��
    * @note ������ϵͳ�����ļ���ģ�ͣ������ϵͳ�����ļ���������Ϣ�ͻ�ȡ������Ϣ�Ľӿ�
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
		std::string                m_strEarthPath;			//�������ĵ����ļ�·��
        std::string                m_strSystemTitle;		//��������ϵͳ����
		std::string                m_strSystemIcon;			//����ϵͳ��ͼ��·��
		std::string                m_strFeatureLayerConfig; //ʸ������
		std::string                m_strCustomLayerConfig;  //�û��Զ���ͼ������
		std::string                m_strMarksConfig;		//���ʻ����������ļ�
		std::string                m_strContourConfig;		//ѣ��ͼ��Ĭ����ɫ����
        FeUtil::CFreeViewPoint     m_sViewPointBegin;       //�ӵ��װ��
		FeUtil::CFreeViewPoint     m_sViewPointEnd;			//�ӵ��װ��
    };
}

namespace FeShell
{
    /**
      * @class CSystemConfigLoader
      * @brief ϵͳ���õ����л���
      * @note ���л�ϵͳ���õ���Ϣ���������ļ��л��ϵͳ����Ҫ����Ϣ
      * @author l00008
    */
    class FESHELL_EXPORT CSystemConfigLoader :public FeUtil::TiXmlVisitor
    {
    public:
        CSystemConfigLoader();
        ~CSystemConfigLoader();

		///���ָ���������ļ�������Ϣ
        bool Execute(const std::string& strFileName, CSysConfig& systemConfig);

		///���Ĭ�ϵ������ļ��µ�������Ϣ
		bool ExecuteDefault(CSysConfig& systemConfig);

    public:
        virtual bool VisitEnter(const FeUtil::TiXmlElement& ele , const FeUtil::TiXmlAttribute* attr);

    protected:
        bool AcceptCommon(const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr);

		bool AcceptViewPoint(const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr);

		void BuildViewPoint(const FeUtil::TiXmlElement* pElement, FeUtil::CFreeViewPoint& viewPoint);

    protected:
        CSysConfig      m_configModule; //ϵͳ��������ģ��
    };
}

#endif//SHELL_SYSTEM_CONFIG_SERIALIZER_H
