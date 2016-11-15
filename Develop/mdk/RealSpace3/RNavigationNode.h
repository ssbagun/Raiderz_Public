#ifndef _RNAVIGATION_NODE_H
#define _RNAVIGATION_NODE_H

#include "RTypes.h"
#include "RLine.h"
#include "RAStar.h"
#include <vector>
#include <list>

using namespace std;

namespace rs3 {

class RNavigationNode : public RAStarNode
{
public:
	enum NODE_VERT
	{
		VERT_A = 0,
		VERT_B,
		VERT_C
	};

	enum NODE_SIDE
	{
		SIDE_AB = 0,
		SIDE_BC,
		SIDE_CA
	};

	enum PATH_RESULT
	{
		NO_RELATIONSHIP,		// the path does not cross this node
		ENDING_NODE,			// the path ends in this node
		EXITING_NODE,			// the path exits this node through side X
	};
private:
	int					m_nID;
	RPlane				m_Plane;
	RVector				m_Vertex[3];
	
	RNavigationNode*	m_Links[3];
	rline2d				m_Side[3];
	RVector				m_WallMidpoint[3];	// the pre-computed midpoint of each wall.
	float				m_WallDistance[3];	// the distances between each wall midpoint of sides (0-1, 1-2, 2-0)
	int					m_nArrivalLink;

	void ComputeNodeData();
protected:
public:
	RVector				m_CenterPos;
	

	RNavigationNode();
	virtual ~RNavigationNode();

	void Init(int nID, const RVector& v1, const RVector& v2, const RVector& v3);
	

	RNavigationNode& operator=( const RNavigationNode& Src);
	void SetLink(NODE_SIDE side, RNavigationNode* pCaller);
	RNavigationNode* GetLink(int side) const;
	bool RequestLink(const RVector& PointA, const RVector& PointB, RNavigationNode* pCaller);

	bool ForcePointToNodeColumn(RVector2& TestPoint) const;
	bool ForcePointToNodeColumn(RVector& TestPoint)const;
	bool IsPointInNodeColumn(const RVector& TestPoint) const;
	bool IsPointInNodeColumn(const RVector2& TestPoint) const;
	void MapVectorHeightToNode(RVector& MotionPoint)const;
	PATH_RESULT ClassifyPathToNode(const rline2d& MotionPath, RNavigationNode** ppNextNode, 
									NODE_SIDE& side, RVector2* pPointOfIntersection) const;

	const RVector& Vertex(int Vert) const;
	const RVector& CenterVertex() const;
	int GetID() { return m_nID; }

	// test
	virtual float GetSuccessorCost(RAStarNode* pSuccessor);
	virtual float GetHeuristicCost(RAStarNode* pGoal);
	virtual int GetSuccessorCount()							{ return 3; }
	virtual RAStarNode* GetSuccessor(int i)					{ return m_Links[i]; }
	virtual void OnSetData(int nSuccessorIndex, RAStarNode* pParent)
	{
		for ( int i = 0 ; i < 3 ; ++i )
		{
			if (m_Links[i] == NULL) continue;
			if (pParent == m_Links[i])
                m_nArrivalLink = i;
		}
	}
	int GetArrivalLink()	{ return m_nArrivalLink; }
	RVector& GetWallMidPoint(int side) { return m_WallMidpoint[side]; }

	bool bSelected;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////
inline RNavigationNode& RNavigationNode::operator=( const RNavigationNode& Src)
{
	if (this != &Src)
	{
		m_nArrivalLink	= Src.m_nArrivalLink;
		m_nID			= Src.m_nID; 
		m_Plane			= Src.m_Plane;
		bSelected		= Src.bSelected;
		m_CenterPos		= Src.m_CenterPos;

		for (int i=0;i<3;++i)
		{
			m_Vertex[i] = Src.m_Vertex[i];
			m_Links[i]	= Src.m_Links[i];
			m_Side[i]	= Src.m_Side[i];
			m_WallMidpoint[i] = Src.m_WallMidpoint[i];
		}
	}
	return (*this);
}

inline void RNavigationNode::SetLink(NODE_SIDE side, RNavigationNode* pCaller)
{
	m_Links[side] = pCaller;
}

inline RNavigationNode* RNavigationNode::GetLink(int side) const
{
	return (m_Links[side]);
}

inline const RVector& RNavigationNode::Vertex(int Vert) const
{
	return (m_Vertex[Vert]);
}

inline const RVector& RNavigationNode::CenterVertex() const
{
	return m_CenterPos;
}

}

#endif
