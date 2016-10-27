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
     * @brief 环境配置文件
     * @note 定义了环境配置文件，保存和环境配置文件的数据信息和获取数据信息的接口
     * @author x00028
   */
     class FESHELL_EXPORT CEnvConfig 
 	{
 	public:
 		//语言的Key以及对应的语言解析文件的文件名 
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
 		bool                        m_bValid;           //是否合法
 
 		EnvMap						m_mapEnv;
     };
 }
 
 namespace FeShell
 {
     /**
       * @class CEnvConfigReader
       * @brief 语言配置的序列化器
       * @note 序列化系统语言配置的信息，将配置文件读入map
       * @author x00028
     */
     class FESHELL_EXPORT CEnvConfigReader :public FeUtil::TiXmlVisitor
     {
     public:
         CEnvConfigReader();
         ~CEnvConfigReader();
 
  		///获得指定的配置文件配置信息
          CEnvConfig Execute(const std::string& strFileName);
  
      public:
          virtual bool VisitEnter(const FeUtil::TiXmlElement& ele , const FeUtil::TiXmlAttribute* attr);
  
      protected:
          bool AcceptEnv(const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr);
 
     protected:
         CEnvConfig      m_configModule; //系统语言配置数据模型
     };
 
 	/**
       * @class CEnvConfigWriter
       * @brief 语言配置的序列化器
       * @note 序列化系统语言配置的信息，从map写入配置文件
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
