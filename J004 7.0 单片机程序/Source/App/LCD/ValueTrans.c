#include "ValueTrans.h"

//将数值按格式缩放
u16 Value2Show(u16 value,const ST_FormatScript* pFormat)
{
	u16 mid,midh;
	u32 mid32;

	if(value<pFormat->ValueMin)
		return pFormat->ShowMin;

	if((pFormat->ShowMax-pFormat->ShowMin)==(pFormat->ValueMax-pFormat->ValueMin))
		return value-pFormat->ValueMin+pFormat->ShowMin;

	mid = pFormat->ValueMax-pFormat->ValueMin;
	midh = mid>>1;
	if(mid!=0)
	{		
		mid32 = pFormat->ShowMax-pFormat->ShowMin;
		mid32 = (mid32*(value-pFormat->ValueMin)+midh)/mid
				+pFormat->ShowMin;
		if(mid32>65535)
			mid = 65535;
		else
			mid = mid32;
	}
	else
		mid = value;

	return mid;
}
//将显示的值按格式缩放到内部数值
u16 Show2Value(u16 value,const ST_FormatScript* pFormat)
{
	u16 mid,midh;
	u32 mid32;

	if(value<pFormat->ShowMin)
		return pFormat->ValueMin;

	if((pFormat->ShowMax-pFormat->ShowMin)==(pFormat->ValueMax-pFormat->ValueMin))
		return value-pFormat->ShowMin+pFormat->ValueMin;		
	
	mid = pFormat->ShowMax-pFormat->ShowMin;
	midh = mid>>1;
	if(mid!=0)
	{		
		mid32 = pFormat->ValueMax-pFormat->ValueMin;
		mid32 = (mid32*(value-pFormat->ShowMin)+midh)/mid
				+pFormat->ValueMin;
		if(mid32>65535)
			mid = 65535;
		else
			mid = mid32;
	}
	else
		mid = value;

	return mid;
}

//将数据转化为字符串
u8 Value2Str(u8* str,u16 value,const ST_FormatScript* pFormat)
{
	u8 bNegtive;
	u8* pBuf;
	u8 buf;
	u8 size;
	u8 pt;
	u8 fraction;
	u8 integer;

	bNegtive = FALSE;
	pBuf = str;

	if(pFormat->ShowOffset!=0)
	{
		if(value>=pFormat->ShowOffset)
			value -= pFormat->ShowOffset;
		else
		{
			bNegtive = TRUE;
			value = pFormat->ShowOffset-value;
		}
	}

	size =0;
	if(pFormat->fraction!=0)
	{
		for(fraction = pFormat->fraction;fraction>0;fraction--)
		{
			*pBuf++ = value%10+'0';
			value /= 10;			
			size++;
		}
		*pBuf++ = '.';
		size++;
	}

	integer = pFormat->integer;
	while(integer>0)
	{
		*pBuf++ = value%10+'0';
		value /= 10;			
		size++;
		if((!(pFormat->Flags&VFM_FILL))&&(value==0))
			break;
		integer--;
	}

	if(bNegtive)
	{
		*pBuf++ = '-';
		size++;
	}
	*pBuf = '\0';

	for(pt = size>>1;pt>0;pt--)
	{
		buf = *str;
		pBuf--;
		*str++ = *pBuf;
		*pBuf = buf;
	}
	
	return size;
}

//将字符串按格式转化为数据
u8 Str2Value(u8* str,u16* pValue,const ST_FormatScript* pFormat)
{	
	u8* pBuf;
	u16 value;
	u32 mid;
	u8 bNegtive;
	u8 fraction;
	u8 bHavePt;
	
	pBuf = str;
	if(*pBuf=='-')
	{
		bNegtive = 1;
		pBuf++;
	}
	else
		bNegtive = 0;

	fraction = pFormat->fraction;
	bHavePt = 0;
	for(value = 0;*pBuf!=0;pBuf++)
	{
		if(*pBuf>='0'&&*pBuf<='9')
		{
			mid = value*10+(*pBuf-'0');			
			if(mid>65535)
			{
				*pValue=pFormat->ShowMax;
				return 0;
			}
			else
				value = mid;
		}
		else if(*pBuf=='.'&&!bHavePt)
		{
			bHavePt = 1;
			continue;
		}
		else
			break;

		if(bHavePt)
		{
			if(fraction)
				fraction--;
			if(fraction==0)
				break;
		}
	}
	
	for(;fraction>0;fraction--)
	{
		mid = value*10;
		if(mid>65535)
		{
			*pValue=pFormat->ShowMax;
			return 0;
		}
		else
			value = mid;
	}

	if(pFormat->ShowOffset!=0)
	{
		if(bNegtive)
		{
			if(value>=pFormat->ShowOffset)
				value-=pFormat->ShowOffset;
			else
			{
				*pValue = pFormat->ShowMin;
				return 0;
			}
		}
		else
		{
			if((65535-value)>=pFormat->ShowOffset)
				value+=pFormat->ShowOffset;
			else
			{
				*pValue = pFormat->ShowMax;
				return 0;
			}
		}
	}
	
	if(value>pFormat->ShowMax)
	{
		*pValue = pFormat->ShowMax;
		return 0;
	}
	if(value<pFormat->ShowMin)
	{ 
		*pValue = pFormat->ShowMin;
		return 0;
	}

	*pValue = value;
	return 1;
}

//在字符串中寻找字符
s8 SeekinStr(u8* str,u8 character)
{
	s8 result;
	for(result=0;*str!=0;str++,result++)
	{
		if(*str==character)
			return result;
	}
	return -1;
}

//在代表数值的字符串后增加字符
u8 AddCharValue(u8* str,u8 num,const ST_FormatScript* pFormat)
{
	u8* pBuf;
	u8 pt;
	u8 tmp;
	s8 ptpt;

	for(pt=0,pBuf=str;*pBuf!=0;pt++,pBuf++);

	if(num == '-')
	{
		if(pt==1&&str[0]=='0')
		{
			pt = 0;
			pBuf = str;
		}
		
		if(pt!=0)
			return pt;
		if(pFormat->ShowOffset==0)
			return pt;
	}
	else if(num == '.')
	{
		if(pFormat->fraction==0)
			return pt;

		if(pt==0)
		{
			*pBuf++ = '0';
			*pBuf++ = '.';
			*pBuf = 0;
			return 2;
		}

		if(SeekinStr(str,'.')>=0)
			return pt;

	}
	else if(num>='0'&&num<='9')
	{		
		ptpt = SeekinStr(str,'.');
		if(str[0]=='0'&&pt==1)
		{	
			str[0] = num;
			return pt;
		}

		if(ptpt<0)
		{
			tmp = 0;
			if(str[0]=='-')
				tmp = 1;

			if(pt>=pFormat->integer+tmp)
					return pt;
			
		}
		else
		{
			if((pt-ptpt)>pFormat->fraction)
				return pt;
		}
	
	}
	else
		return pt;

	*pBuf++ = num;
	*pBuf = 0;
	return pt+1;

}
