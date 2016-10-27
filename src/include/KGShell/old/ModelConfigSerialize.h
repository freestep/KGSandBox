#ifndef HG_MODEL_CONFIG_SERILIZE_H
#define HG_MODEL_CONFIG_SERILIZE_H

#include <osgEarth/Viewpoint>

#include <FeUtils/tinyXml/tinyxml.h>
#include <FeUtils/tinyXml/tinyutil.h>

#include <FeUtils/FreeViewPoint.h>
#include <FeShell/Export.h>


namespace FeShell
{
	struct ModelInfo 
	{
		std::string strModelCatagory;
		std::string strModelName;
		std::string strModelPath;
		std::string strModelIcon;
		std::string strDescribe;
	};

	class FESHELL_EXPORT CModelConfig
	{
	public:
		CModelConfig();
		~CModelConfig();

	public:
		bool Valid();
		void SetValid(bool bValue);

		std::vector<ModelInfo*>* GetModelInfo() const;
		void SetModelInfo(std::vector<ModelInfo*>* vecModelInfo);

		void SetMapOfModelInfo(const std::map<std::string,ModelInfo> &mapStrModelInfo );
		std::map<std::string,ModelInfo>* GetMapOfModelInfo();
	private:
		bool							m_bValid;           //是否合法
		ModelInfo						m_SModelInfo;		// 模型信息
		std::string						m_strModelConfigPath;	//模型配置文件路径
		std::vector<ModelInfo*>*		m_vecModelInfo;	    // 模型信息集合

		std::map<std::string,ModelInfo> m_mapStrModelInfo;

	};
}

namespace FeShell
{

	class FESHELL_EXPORT CModelConfigDeSerialization : public FeUtil::TiXmlVisitor
	{
	public:
		CModelConfigDeSerialization();
		~CModelConfigDeSerialization();

		///获得指定的配置文件配置信息
		CModelConfig Execute(const std::string& strFileName);

	public:
		virtual bool VisitEnter(const FeUtil::TiXmlElement& ele , const FeUtil::TiXmlAttribute* attr);

	protected:
		bool AcceptModel( const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr );

	protected:
		CModelConfig      m_configModule; //系统配置数据模型
	};

}

namespace FeShell
{
	class FESHELL_EXPORT CModelConfigSerialization
	{
	public:
		CModelConfigSerialization();
		~CModelConfigSerialization();

		///获得指定的配置文件配置信息
		bool Execute(CModelConfig modelConfig,const std::string& strFileName);
	};
}



#endif //HG_MODEL_CONFIG_SERILIZE_H


