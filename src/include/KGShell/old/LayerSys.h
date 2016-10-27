/**************************************************************************************************
* @file LayerSys.h
* @note 主要封装了图层模块
* @author l00008
* @data 2014-7-19
**************************************************************************************************/
#ifndef HG_LAYER_SYSTEM_CALL_H
#define HG_LAYER_SYSTEM_CALL_H

#include <osgEarth/ImageLayer>
#include <osgEarth/ElevationLayer>
#include <osgEarth/ModelLayer>
#include <osgEarth/TerrainEffect>

#include <FeShell/Export.h>
#include <FeUtils/SceneSysCall.h>

namespace FeShell
{
	/**
	* @class CFeEffectLayer
	* @brief 特效图层
	* @note 封装特效图层，提供特效图层的显示和隐藏操作
	* @author l00008
	*/
	class FESHELL_EXPORT CFeEffectLayer : public osgEarth::Layer
	{
	public:
		CFeEffectLayer();
		CFeEffectLayer(
			osgEarth::TerrainEffect* pEffectLayer, 
			osgEarth::TerrainEngineNode* pTerrainNode, 
			const std::string& strName,
			bool bVisible);
		virtual ~CFeEffectLayer();

	public:
		/**
		*@note: 设置显隐状态
		*/
		void setVisible(bool bVisible);
		bool getVisible() const;

		/**
		*@note: 设置需要封装的osgEarthEfect
		*/
		void SetEffectLayer(osgEarth::TerrainEffect* pEffectLayer);

		/**
		*@note: 获得封装的osgEarthEfect
		*/
		osgEarth::TerrainEffect* GetEffectLayer();

		/**
		*@note: 设置MapNode
		*/
		void SetTerrainEngineNode(osgEarth::TerrainEngineNode* pTerrainNode);

		/**
		*@note: 获得名称
		*/
		virtual const std::string& getName() const;
		virtual void setName(const std::string& strName);

	protected:
		osg::observer_ptr<osgEarth::TerrainEngineNode>      m_opTerrainNode;
		osg::ref_ptr<osgEarth::TerrainEffect>               m_rpEffectLayer;
		bool                                                m_bVisible;
		std::string                                         m_strName;

	};

	typedef std::vector< osg::ref_ptr<CFeEffectLayer> > EffectLayerVector;
}

namespace FeShell
{
	const std::string LAYER_SYSTEM_CALL_DEFAULT_KEY("LayerSystem");

	/**
	* @class CLayerSys
	* @brief 图层系统
	* @note 图层系统，封装获得图层或者其他的操作
	* @author l00008
	*/

	class FESHELL_EXPORT CLayerSys : public FeUtil::CSceneSysCall
	{
	public:
		CLayerSys();

		typedef std::vector< osg::ref_ptr<osgEarth::ModelLayer> > LayerList;

		typedef std::map< std::string, LayerList > LayersLevelMap;
		typedef std::map< int, LayersLevelMap > LayersIndexMap;
		typedef std::map<std::string,LayersIndexMap > LayersTypeMap;

	public:
		/**
		*@note: 获得影像图层
		*/
		void GetImageLayers(osgEarth::ImageLayerVector& vecLayer);

		/**
		*@note: 获得地形图层数据
		*/
		void GetTerrainLayers(osgEarth::ElevationLayerVector& vecLayer);

		/**
		*@note: 获得模型数据图层
		*/
		void GetModelLayers(osgEarth::ModelLayerVector& vecLayer);

		/**
		*@note: 获得Shp图层文件结合
		*/
		void GetShpLayers(osgEarth::ModelLayerVector& vecLayer);

		/**
		*@note: 获得矢量图层
		*/
		//void GetVectorLayers(osgEarth::HgLayerVector& vecLayer);

		/**
		*@note: 获得特效图层
		*/
		void GetEffectLayers(EffectLayerVector& vecLayer);

		template<typename T>
		T* GetEffectLayer() 
		{
			osgEarth::MapNode* pMapNode = m_opRenderContext->GetMapNode();
			if(pMapNode)
			{
				osgEarth::TerrainEngineNode* pEngineNode = pMapNode->getTerrainEngine();
				if(pEngineNode)
				{
					return pEngineNode->getEffect<T>();
				}
			}

			return NULL;
		}

	///扩展的接口，将Feature分类显示
	public:

		/**
		*@note: 获得Feature图层
		*/
		void GetTypeFLayer(LayersTypeMap &mapTypeLayer);

		/**
		*@note: 获得全局的Feature
		*/
		void GetGlobalFLayer(osgEarth::ModelLayerVector& vecLayer);

	public:
		/**
		*@note: 添加一个高程图层，并返回添加的图层
		*/
		osgEarth::ElevationLayer* AddElevationLayer(const std::string strPath);

		/**
		*@note: 添加一个高程图层，并返回添加的图层
		*/
		bool AddElevationLayer(osgEarth::ElevationLayer* pLayer);

		/**
		*@note:删除一个高程图层
		*/
		bool DeleteElevationLayer(osgEarth::ElevationLayer* pLayer);

		/**
		*@note: 添加一个卫星图片图层，并返回添加的图层
		*/
		osgEarth::ImageLayer* AddImageLayer(const std::string strPath);
		
		/**
		*@note: 添加一个卫星图片图层，并返回添加的图层
		*/
		bool AddImageLayer(osgEarth::ImageLayer* pLayer);
		
		/**
		*@note:删除一个高程图层
		*/
		bool DeleteImageLayer(osgEarth::ImageLayer* pLayer);

		/**
		*@note: 添加一个矢量图层，并返回添加的图层
		*/
		osgEarth::ModelLayer* AddFeatureLayer(const std::string strPath);
				
		/**
		*@note: 添加一个矢量图层，并返回添加的图层
		*/
		bool AddFeatureLayer(osgEarth::ModelLayer* pLayer);

		/**
		*@note:删除一个矢量图层
		*/
		bool DeleteFeatureLayer(osgEarth::ModelLayer* pLayer);
			
		/**
		*@note:删除一个矢量图层
		*/
		bool DeleteLayer(osgEarth::Layer* pLayer);

		/**
		*@note: 添加一个颜色过滤器
		*/
		void AddImageColorFilter(osgEarth::ColorFilter* pColorFilter);

		/**
		*@note: 移除一个颜色过滤器
		*/
		void RemoveImageColorFilter(osgEarth::ColorFilter* pColorFilter);
		void RemoveImageColorFilters();

		/**
		*@note: 判断一个颜色过滤器是否被注册
		*/
		//bool IsImageColorInstall(osgEarth::ColorFilter* pColorFilter){};

		///获得用户配置的图层配置路径
		std::string GetCustomConfigPath() const;

		///获得用户配置的图层配置路径
		void SetCustomConfigPath(const std::string& strPath);

		///获得用户配置的高程着色配置路径
		std::string GetContourConfigPath() const;

		///获得用户配置的高程着色配置路径
		void SetContourConfigPath(const std::string& strPath);

	protected:
		/**
		*@note: 实现本系统模型需要的初始化和反初始化函数，此函数在父类中已经调用
		*/
		virtual bool InitiliazeImplement();
		virtual bool UnInitiliazeImplement();

	protected:
		virtual ~CLayerSys();

		///获得Map
		osgEarth::Map* GetMap();

		///获得特效列表，并初始化
		void UpdateEffectLayer();

		///根据提供的类型过滤ModelLayer的集合
		void FilterModelLayes(const std::string& strType, osgEarth::ModelLayerVector& vecLayer);

		///判断本Layer是否是制定的类型，类型使用字符串表示
		bool IsType(const std::string& strType, osgEarth::ModelLayer* pLayer);

		void CreateMapLevelLayer(LayersTypeMap &levelMap, const osgEarth::ModelLayerVector& lyerVector);
		
	protected:
		std::string					m_strCustomConfigPath;
		std::string					m_strContourConfigPath;
		EffectLayerVector           m_mapEffectLayer; //保存特效图层不被释放

	};

}



#endif//HG_LAYER_SYSTEM_CALL_H
