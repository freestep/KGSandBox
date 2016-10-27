#include <KGGraphs/Graph.h>
#include <KGShell/Exception.h>

using namespace KGShell;

namespace KGGraphs
{

	CKGGraph::CKGGraph()
	{

	}

	bool CKGGraph::buildGraph()
	{
		return true;
	}

	bool CKGGraph::deleteGraph()
	{
		try
		{
			delete this;
			return true;
		}
		catch (KGException& e)
		{
			osg::notify(osg::WARN)<<"Ïú»Ù"<<this->className()<<" Ê±Òì³£¡£"<<std::endl ;
		}
		return false;
		
	}

}