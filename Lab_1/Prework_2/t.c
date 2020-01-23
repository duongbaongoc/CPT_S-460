
/*******************************************************
*                      t.c file                        *
*******************************************************/
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

#define TRK 18
#define CYL 36
#define BLK 1024

#include "ext2.h"
typedef struct ext2_group_desc  GD;
typedef struct ext2_inode       INODE;
typedef struct ext2_dir_entry_2 DIR;
GD    *gp;
INODE *ip;
DIR   *dp;

char buf1[BLK], buf2[BLK];
int color = 0x0A;
u8 ino;

main()
{
  u16    i, iblk;
  char   c, temp[64];

  prints("read block# 2 (GD)\n\r");
  getblk(2, buf1);

// 1. WRITE YOUR CODE to get iblk = bg_inode_table block number
	gp = (GD*) buf1;
	iblk = (u16)gp->bg_inode_table;
  prints("inode_block="); putc(iblk+'0'); prints("\n\r"); 

// 2. WRITE YOUR CODE to get root inode
  prints("read inodes begin block to get root inode\n\r");
	getblk(iblk, buf1);
	//root INODE is #2, INODE numbers start from 1
	ip = (INODE*) buf1 + 1;

// 3. WRITE YOUR CODE to step through the data block of root inode
  prints("read data block of root DIR\n\r");
	//check direct data blocks only because testing shows no indirect data blocks
	
  for (i=0; i<12; i++)
	{
		if (ip->i_block[i] == 0)
		{
			break;
		}
		getblk((u16)(ip->i_block[i]), buf2);
		dp = (DIR*)buf2;
		// 4. print file names in the root directory /
		prints(dp->name);
	}
}  

int prints(char *s)
{
	while(*s != '\0')
	{
		putc(*s);
		s++;
	}
	return 0;
}

int gets(char s[])
{
	char c;
	int i = 0;
	while (1)
	{
		c = getc();
		if (c == '\r')
		{
			break;
		}
		s[i] = c;
		i++;
	}
	s[i] = 0;
	return 0;
}

int getblk(u16 blk, char *buf)
{
  // readfd( (2*blk)/CYL, ( (2*blk)%CYL)/TRK, ((2*blk)%CYL)%TRK, buf);
  readfd( blk/18, ((blk)%18)/9, ( ((blk)%18)%9)<<1, buf);
}
/*
//print out u32 number
int print_u32(u32 n)
{
	if (n/10 >= 1)
	{
		print_u32((u32)(n/10));
	}
	putc((n%10)+'0');
	return 0;
}*/

