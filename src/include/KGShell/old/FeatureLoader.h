#ifndef HG_FESHELL_FEATURE_LOADER_H
#define HG_FESHELL_FEATURE_LOADER_H
#include <osgEarth/MapNode>

#include <FeShell/Export.h>

namespace FeShell
{
	/**
	* @class CFeatureLoader
	* @brief 地理要素加载器
	* @note 加载配置文件中配置的地理要素
	* @author l00008
	*/
	class CFeatureLoader
	{
	public:
		CFeatureLoader(const std::string& strFile, osgEarth::MapNode* pMapNode );

		virtual ~CFeatureLoader();

	public:
		/**
		*@note: 加载地理要素文件，通过指定地理要素配置文件路径
		*/
		bool Load();

	protected:
		bool Load(std::istream& in, const osgDB::Options* options );

		void CreateFeature(osgEarth::Config& conf);

	protected:
		std::string    m_strFileName;   //文件名称
		osgEarth::MapNode*    m_pMapNode; //图层文件
	};
}

#endif//HG_FESHELL_FEATURE_LOADER_H
