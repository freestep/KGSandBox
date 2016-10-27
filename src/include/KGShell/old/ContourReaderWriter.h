#ifndef SEHLL_CONTOUR_READER_WRITER_H
#define SEHLL_CONTOUR_READER_WRITER_H

#include <FeShell/Export.h>
#include <FeUtils/tinyXml/tinyxml.h>
#include <FeUtils/tinyXml/tinyutil.h>

#include <string>
#include <map>

#include <osg/Array>

namespace FeShell
{
    /**
    * @class CContourConfigModule
    * @brief 眩晕图的配置信息
    * @author c00005
    */
    class FESHELL_EXPORT CContourConfig
	{
	public:
		//眩晕图的Key以及对应的语言解析文件的文件名 
		typedef std::map<std::string, std::string> ContourMap;

    public:
        CContourConfig();
        ~CContourConfig();

    public:
		bool Valid();
		void SetValid(bool bValue);

		void SetContourList(std::string strKey, std::string strValue);
		void DeleteContourList(std::string strKey);
		ContourMap GetContourList();

		std::string GetDefContour();
		void SetDefContour(std::string strContour);

	private:
		bool                        m_bValid;           //是否合法

		std::string					m_strDefContour;
		ContourMap					m_mapContour;
    };
}

namespace FeShell
{
    /**
      * @class CContourCfgReaderWriter
      * @brief 眩晕图配置的序列化以及反序列化
      * @note 序列化以及反序列化眩晕图配置的信息
      * @author c00005
    */
	class FESHELL_EXPORT CContourCfgReaderWriter :public FeUtil::TiXmlVisitor
	{
	public:
		CContourCfgReaderWriter();
		~CContourCfgReaderWriter();

		//读取配置的功能
	public:
		CContourConfig Read(const std::string& strFileName);

		///获得默认的配置文件下的配置信息
		CContourConfig Read();

	public:
		virtual bool VisitEnter(const FeUtil::TiXmlElement& ele , const FeUtil::TiXmlAttribute* attr);

		bool AcceptContour(const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr);

		//写入配置的功能
	public:
		bool Write(CContourConfig config);

		bool Write(CContourConfig config, const std::string& strFileName);

	protected:
		CContourConfig      m_configModule; //系统眩晕图配置模型
	};
	
	/**
      * @class CContourConfigReader
      * @brief 眩晕图具体的配色方案的读写功能类
      * @author c00005
    */
	class FESHELL_EXPORT CContourReaderWriter : public FeUtil::TiXmlVisitor
	{
	public:
		CContourReaderWriter();

		~CContourReaderWriter();

		//读取功能
	public:
		///获得指定的配置文件配置信息
		osg::Vec4dArray* Read(const std::string& strFileName);

	protected:
		virtual bool VisitEnter(const FeUtil::TiXmlElement& ele , const FeUtil::TiXmlAttribute* attr);

		bool AcceptContour(const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr);


	public:
		bool Write(osg::Vec4dArray* pArray);

		bool Write(osg::Vec4dArray* pArray, const std::string& strFileName);

	protected:
		osg::ref_ptr<osg::Vec4dArray> m_pContourColor; 

	};


}
#endif//SEHLL_CONTOUR_READER_WRITER_H
