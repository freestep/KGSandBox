#ifndef HG_FESHELL_CUSTOM_LAYER_READER_WRITER_H
#define HG_FESHELL_CUSTOM_LAYER_READER_WRITER_H

#include <FeShell/Export.h>

#include <osgEarth/XmlUtils>

namespace FeShell
{
	/**
	* @class CCustomLayerReaderWriter
	* @brief 用户自定义图层配置的读取
	* @note 用于对用户自定义的图层的配置文件进行读写操作
	* @author c00005
	*/
	class FESHELL_EXPORT CCustomLayerReaderWriter
	{
	public:
		CCustomLayerReaderWriter();

		~CCustomLayerReaderWriter();

	public:
		/**
		*@note: 向配置中添加子配置项
		*/
		void AppendConfig(osgEarth::Config config);

		/**
		*@note: 从指定的路径中读取用户自定义图层的配置
		*/
		osgEarth::Config Load(std::string strPath);

		/**
		*@note: 将用户自定义的图层保存到指定的配置文件中
		*/
		bool Save(std::string strPath);

	protected:
		osgEarth::Config	m_rootConfig;
	};
}

#endif//HG_FESHELL_CUSTOM_LAYER_READER_WRITER_H
