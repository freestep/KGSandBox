 #ifndef SHELL_ENVOIRMENT_CONFIG_SERIALIZER_H
 #define SHELL_ENVOIRMENT_CONFIG_SERIALIZER_H
 
 #include <FeShell/Export.h>
 #include <FeUtils/tinyXml/tinyxml.h>
 #include <FeUtils/tinyXml/tinyutil.h>
 
 #include <string>
 #include <map>
 
 namespace FeShell
 {
   /**
     * @class CEnvConfig
     * @brief ���������ļ�
     * @note �����˻��������ļ�������ͻ��������ļ���������Ϣ�ͻ�ȡ������Ϣ�Ľӿ�
     * @author x00028
   */
     class FESHELL_EXPORT CEnvConfig 
 	{
 	public:
 		//���Ե�Key�Լ���Ӧ�����Խ����ļ����ļ��� 
 		typedef std::map<std::string, std::string> EnvMap;
 
     public:
         CEnvConfig();

         ~CEnvConfig();
 
     public:
 		bool GetValid();
 		void SetValid(bool bValue);
 
 		void SetEnvironmentList(std::string strKey, std::string strValue);
 		EnvMap GetEnvironmentList();
 
 	private:
 		bool                        m_bValid;           //�Ƿ�Ϸ�
 
 		EnvMap						m_mapEnv;
     };
 }
 
 namespace FeShell
 {
     /**
       * @class CEnvConfigReader
       * @brief �������õ����л���
       * @note ���л�ϵͳ�������õ���Ϣ���������ļ�����map
       * @author x00028
     */
     class FESHELL_EXPORT CEnvConfigReader :public FeUtil::TiXmlVisitor
     {
     public:
         CEnvConfigReader();
         ~CEnvConfigReader();
 
  		///���ָ���������ļ�������Ϣ
          CEnvConfig Execute(const std::string& strFileName);
  
      public:
          virtual bool VisitEnter(const FeUtil::TiXmlElement& ele , const FeUtil::TiXmlAttribute* attr);
  
      protected:
          bool AcceptEnv(const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr);
 
     protected:
         CEnvConfig      m_configModule; //ϵͳ������������ģ��
     };
 
 	/**
       * @class CEnvConfigWriter
       * @brief �������õ����л���
       * @note ���л�ϵͳ�������õ���Ϣ����mapд�������ļ�
       * @author x00028
     */
 	class FESHELL_EXPORT CEnvConfigWriter : public FeUtil::TiXmlVisitor
 	{
 	public:
 		CEnvConfigWriter();
 
 		virtual ~CEnvConfigWriter();
 
  	public:
  		bool Execute(CEnvConfig pEnvConfig);
  
		bool Execute(CEnvConfig::EnvMap Envmap, const std::string& strFileName);
 
 	};
 }
 
 #endif//SHELL_LAN_CONFIG_SERIALIZER_H
