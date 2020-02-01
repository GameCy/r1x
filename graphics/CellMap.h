#ifndef __TEMPLATE_MAP_H__
#define __TEMPLATE_MAP_H__

template<class T>
class CellMap
{
public:
    CellMap();
    CellMap(int dx, int dy, float minX, float maxX, float minY, float maxY);	// size of array and real coords bounding box for mapping
    virtual ~CellMap();
	void	init(int dx, int dy, float minX, float maxX, float minY, float maxY);

    // maped world coordinates
	void		SetCell	 (float x, float y, T &p);
	T*			GetCell (float x, float y);
	void		SetMapping(float minX, float maxX, float minY, float maxY);

    // unmaped cell coordinates
	inline void		SetCell (int x, int y, T &p)	{ m_pCells[x+y*mapSizeX] = p; };
	inline T*	 	GetCell (int x, int y)	{ return &m_pCells[x+y*mapSizeX]; };

	void	ClearAllCells()	{  memset(m_pCells, 0, mapSizeX*mapSizeY*sizeof(T)); };

	bool	ConvertCoordsf2i(float x, float y, int *i, int*j); //, int *dx, int *dy);	// returns false if out of bounds
    void	ConvertCoordsi2f(int x, int y, float *wcX, float *wcY);		//25 July 2003

	T*		m_pCells;
	int		mapSizeX, mapSizeY;
	float	m_offsetX, m_offsetY, m_factorX, m_factorY, 
			m_cellhdx, m_cellhdy; // half cell size
	float	m_minX, m_minY, m_maxX, m_maxY;

	inline	bool	inbounds(int&x,int&y);
};




template<class T>
CellMap<T>::CellMap(){
	
	m_pCells = 0;
	mapSizeX = 0;
	mapSizeY = 0;
	m_offsetX = 0; m_offsetY = 0; m_factorX = 0; m_factorY = 0;
	m_minX = 0; m_minY = 0; m_maxX = 0; m_maxY = 0;
	m_cellhdx = m_cellhdy = 0;
}


template<class T>
CellMap<T>::CellMap(int dx, int dy, float minX, float maxX, float minY, float maxY)
{
	init(dx, dy, minX, maxX, minY, maxY);
}

template<class T>
CellMap<T>::~CellMap()
{
	if (m_pCells)	{ delete[] m_pCells; m_pCells=0; }
}

template<class T>
void	CellMap<T>::init(int dx, int dy, float minX, float maxX, float minY, float maxY)
{
	m_pCells=0;
	mapSizeX=mapSizeY=0; 
	
	if ( (dx>0) && (dy>0) )	// if sizes are correct
	{
		m_pCells = new T[dx*dy];	
		if (m_pCells )	// if allocated
		{
			mapSizeX=dx; mapSizeY=dy;	// save array size
			memset(m_pCells, 0, dx*dy*sizeof(T));	// clear array
			SetMapping(minX, maxX, minY, maxY);
		}
	}
	m_minX = minX;	m_minY = minY;
	m_maxX = maxX;	m_maxY = maxY;
}

template<class T>
void	CellMap<T>::SetMapping(float minX, float maxX, float minY, float maxY)
{
	m_offsetX = -minX;
	m_offsetY = -minY;
	m_factorX = ((float)mapSizeX)/(maxX-minX);
	m_factorY = ((float)mapSizeY)/(maxY-minY);
	m_cellhdx = 0.5f*(maxX-minX)/((float)mapSizeX);
	m_cellhdy = 0.5f*(maxY-minY)/((float)mapSizeY);
    m_minX = minX;	m_minY = minY;
    m_maxX = maxX;	m_maxY = maxY;
}

template<class T>
void	CellMap<T>::SetCell(float x, float y, T& p)
{
	int i=0, j=0;//, dx=0, dy=0;
	if (ConvertCoordsf2i(x,y,&i,&j)) //,&dx,&dy) )
		SetCell(i, j, p);
}

template<class T>
T*	CellMap<T>::GetCell (float x, float y)
{
	int i=0, j=0; //, dx=0, dy=0;
	if (ConvertCoordsf2i(x,y,&i,&j)) //,&dx,&dy) )
		return (T&) 0xFFFFFFFF;
	return GetCell(i, j);
}

template<class T>
bool	CellMap<T>::ConvertCoordsf2i(float x, float y, int *i, int*j)//, int *dx, int *dy)	// returns false if out of bounds
{
	// find i,j pos in array
	*i = (int)((x-m_minX)*m_factorX);
	*j = (int)((y-m_minY)*m_factorY);
	if ( (*i<0) || (*j<0) || (*i>(mapSizeX-1)) || (*j>(mapSizeY-1)) )
		return false;

	return true;
}

template<class T>
void CellMap<T>::ConvertCoordsi2f(int cellX, int cellY, float *wcX, float *wcY){

	(*wcX) = m_minX + (float)cellX*(m_maxX - m_minX)/(float)mapSizeX;
	(*wcY) = m_minY + (float)cellY*(m_maxY - m_minY)/(float)mapSizeY;

}

template<class T>
bool	CellMap<T>::inbounds(int&x,int&y)
{
	if ( (x<0) || (y<0) || (x>=mapSizeX) || (y>=mapSizeY) )
		return false;
	return true;
}

#endif
