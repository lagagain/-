#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define DEBUG 



/***************�����]�w*********************/
struct question{
	char *Q;
	int isq;
	char *A1;
	char *A2;
	char *A3;
	char *A4;
	int next[4];
};

struct question nQ[15];

int reset(void)
{
	int i=1;
/*	for(i=1;i<15;i++)
	{
		nQ[i].Q=(char*)calloc(50,sizeof(char));
		nQ[i].A1=(char*)calloc(50,sizeof(char));
		nQ[i].A2=(char*)calloc(50,sizeof(char));
		nQ[i].A3=(char*)calloc(50,sizeof(char));
		nQ[i].A4=(char*)calloc(50,sizeof(char));
	}
*/	
	nQ[1].Q="1�B�b�Q�װϤ��A�p�G���H��A�ҵo�����פj�O�R�ѡA�Ʀܤf�X�c���A�A�������|�O�G";
	nQ[1].A1="A�B�j�a�������צۥѡA�H�K�L�I";
	nQ[1].A2="B�B���ضW���n�A���L�٬O�o�������סA�d���ХL�ۭ��n�F�C";
	nQ[1].A3="C�B�d����H�~�M���|�ڡA��M�@�w�n�|�^�h�I";
	nQ[1].A4="D�B��S�̡A�s���ͦb�����W�@�_��ϥL�C";
	for(i=0;i<4;i++)
		nQ[1].next[i]=i+2;
	nQ[1].next[3]=2;
	nQ[1].isq=1;
	
	nQ[2].Q="2�B �bKTV�w�۱o��high�ɡA���J����M���F�F�A�n�����������A��^���W�N�F�U�ӡA�o�ɧA�|�G";
	nQ[2].A1="A�B���ӬO�u�������D�A�j�a���ְʤ��ˬd�ݬݡC";
	nQ[2].A2="B�B�֡H�O�֦b�d���H�@�w�O�b�����H�G�N�o�áI";
	nQ[2].A3="C�B�����I�s�A�ȤH���ӡA�ڭn�ȶD�I";
	nQ[2].A4="D�B��F�A���ۤF�A�u�����C";
	nQ[2].isq=1;
	nQ[2].next[0]=3;
	nQ[2].next[1]=5;
	nQ[2].next[2]=4;
	nQ[2].next[3]=6;
	
	nQ[3].Q="3�B �@�}�l�S�p�����B�ͳ̪�X���ܱo�ܤj��A�M�L�X�h�ѬO���w�R��ЫȡA�A���A�׷|�O�H";
	nQ[3].A1="A�B�z�I���Ӧ������B�ͯu�n�I�H��@�w�n�n�n�O���p���C";
	nQ[3].A2="B�B�Z�հݥL�G�A�O���O���ֳz�F�H";
	nQ[3].A3="C�B�Pı���I�Q���A�j�a���B�ͷF���n�d���šA�A�O�ݧڽa�O�a�H";
	nQ[3].A4="D�B�d���n�L�O���F���򨣤��o�H���ķ�A�٬O�O���Z���������C";
	nQ[3].isq=1;
	nQ[3].next[0]=5;
	nQ[3].next[1]=6;
	nQ[3].next[2]=5;
	nQ[3].next[3]=6;
	
	nQ[4].Q="4�B �M�Y�Ӻ��ͬ۽ͬ��w�A�M�w���X�Ө��������ѡA�����F�O�I�_���A�٬O���b���@���Ҩ�������w���A�o�ɧA�|�G";
	nQ[4].A1="A�B�����įP�A��M�n��������Ǯɭu���I";
	nQ[4].A2="B�B�ȹ��䤣��A���٬O������w�a�I���ۦn�F�C";
	nQ[4].A3="C�B���Ȥ@�U�A�u�ȸU�@�A�p�G���O���s���H�٬O�b���������f��A�M�w�n���n�{���C";
	nQ[4].A4="D�B�S����n�������ê��A��Ǯɨ�N�Ǯɨ�a�I";
	nQ[4].isq=1;
	nQ[4].next[0]=5;
	nQ[4].next[1]=5;
	nQ[4].next[2]=6;
	nQ[4].next[3]=3;
	
	nQ[5].Q="5�B ���Ѻ��@�ت��H�W�h�A��m�u�ѤU�ù����V�~�䪺���@�ӡA�ө���H��ù��ت����e�@���L��A�o�ɧA�|��ܡG";
	nQ[5].A1="A�B�H�K�աI���o��������n�I";
	nQ[5].A2="B�B�����ꪺ��m�֭n���I���a�աI";
	nQ[5].A3="C�B�J�M�i�ӤF�A��b���n�N�仡���n�A�ԭ@�@�Ӥp�ɦn�F�C";
	nQ[5].A4="D�B�o�Ӧ�m�����ڡI�ϥ��ڤS���ȤH�ݡA�����ئ��������Y�H";
	nQ[5].isq=1;
	nQ[5].next[0]=6;
	nQ[5].next[1]=7;
	nQ[5].next[2]=7;
	nQ[5].next[3]=8;
	
	nQ[6].Q="6�B �M���ئ��I���w���H�X�h�ܩ@�ءA��ԲD�n�y�H�A��^���n�A�I��ɡA�������A�׫o�Q���c�H�A�o�ɧA�|�G";
	nQ[6].A1="A�B�߷Q�G�o�a�����A�ȺA�ׯu�t�A�U�������ڤ]���ӤF�I";
	nQ[6].A2="B�B�d����I�A�׳o��t�A�ڤ]���|���A�n�y��ݪ��I";
	nQ[6].A3="C�B�b���w���H���e�٬O�O�����קa�A�U���A���ڸI��A�N���D���ݤF�I";
	nQ[6].A4="D�B�N�N�a���G�A���A�ȺA�פ@�V���o��n�ܡH";
	nQ[6].isq=1;
	nQ[6].next[0]=7;
	nQ[6].next[1]=7;
	nQ[6].next[2]=8;
	nQ[6].next[3]=8;
	
	
	nQ[7].Q="7�B ���F�ݤ��P�A�A�R�F�@�O�����ƪ��滷��A�����ۡA���p�����O�H�a�h�F�A�A�|�Ʊ�Ө쪺�a��O�G";
	nQ[7].A1="A�B�o�٥λ��A��M�O�����k�~�����D�ǡC";
	nQ[7].A2="B�B�׫ǡI�ݬݦ��S���E���e���i�H�Y��C";
	nQ[7].A3="C�B�ڿ��F�ڿ��F�I���I��}�~��I ";
	nQ[7].A4="D�B�Y��Y��O�H�a�]�����A�����N�ݨ��ù�I ";
	nQ[7].isq=1;
	nQ[7].next[0]=8;
	nQ[7].next[1]=8;
	nQ[7].next[2]=14;
	nQ[7].next[3]=12;
	
	
	nQ[8].Q="8�B �hShopping�ɡA�]���H�Ӧh�F�A����ɤp�j���Ȧh��F�A���A�Ʀܳs�A�R���F��]���K�u�ɯšv�F�A�o�ɧA�|�G";
	nQ[8].A1="A�B�u�ɯšv���F�褣���o�ŦX�ڪ��ݭn�A�F���M�٬O�n���^�Ӥ���n�C ";
	nQ[8].A2="B�B������F�O�o������A�i�ڤf�U���F����٦��٦^�h���D�z�A�s�o�ۧ@�ۨ��a�C ";
	nQ[8].A3="C�B�F���M�ۤv�L���h�ڡA�ள�N���A�N��@���ѬOlucky day�A�q�q���U�ӧa�I ";
	nQ[8].A4="D�B���i�H�����H�a�O�H��F���٦^�h�A���K��o�n�q�ܦn�F�I ";
	nQ[8].isq=1;
	nQ[8].next[0]=13;
	nQ[8].next[1]=10;
	nQ[8].next[2]=9;
	nQ[8].next[3]=11;
	
	nQ[9].Q="A ���]���}����ǧJ\n\t�A�߬��⻶�A���������藍�|�æb�߲z�A�����n�@�w�n�o�n�X�ӡA�A���y�k�ʬO�u���������v�A���M���ɭԤ]�|�A�I�p���I�A���j�h�ɭԪ��A�`�O�i�H���H�Pı��A���������ʮ�C";
	nQ[9].isq=0;
	nQ[10].Q="B ���]������\n\t�S���I�A�N�O�f�u���ꪺ�a�F�l�I�γ\�A�]���g�۫H�L�H�ʥ����A���O�ݦh�F�H���୮�����@����A�A���F��Ӭ۫H�H�ʥ��c���~�A�Ʀ��ٱ`�`���v�O�H���a�ơA�ɹɹɡK�K�G�M�ܦ���c�]����O�ڡI";
	nQ[10].isq=0;
	nQ[11].Q="C ���]�����]�k\n\t�A���өʴN�O����j�F��ǡA�p�G�o�ӯS��i�H�n�n�o�����ܡA�|�\�A�]�ন���ѨϤ]���@�w�F���L�A�����n�B�J�[�~�A�ҥH�ѬO�R�Φۤv���p�o���@�˧O�H�A�p�߰ڡI�o���]���Q�o���~���@�ѰڡI";
	nQ[11].isq=0;
	nQ[12].Q="D ���]����C\n\t�A�o�ӤH�E�ݤ��U���G�L�r�L�`�A���`�ݰ_�Ӥ]�@�I�D�����M���ҼˡA���O�u�n���A���a�p�B�뤤�A���n�`�A����A�ܥi��N�ߨ�½�y���{�H�A���W��g�_�ӡA���������t�Ӥj�A���H�ȩȰڡI";
	nQ[12].isq=0;
	nQ[13].Q="E ���]�����ذ�\n\t��껡�_�ӡA�A�ä����O�u�c�]�v�A�j���u�ٱo�W�O�u���I�a�߲��v�Ӥw�C�]���M�u�����c�]��_�ӡA���ɭԧA��b�ӹL���}�A���M�ѨϤ�_�ӧA�S�����¼�A���W���U���A�A�ܥi��b�O�H�����v���U���a�Ƴ�I";
	nQ[13].isq=0;
	nQ[14].Q="F ���]������ù\n\t�o�򻡧a�I���A�����}�M���c��@���A���o�K���@�I�A�N���O�u���D�q���j���v�N��F�I�A�ä��|�H�N���D�@��A�j�h�ƮɭԧA�u�O���B�ͥS�̥X�Y�Ӥw�A�ҥH�o�˪��өʭˬO�ܨ���j�a���w����I";
	nQ[14].isq=0;
	
	
	for(i=9;i<15;i++)
	{
		nQ[i].isq=0;
	}

}

int chans(char);	//�ŧi�P�_���

 
/*************�D�{��******************/ 
int main(void)
{
	reset();
	int i;
	int n=1;
	char cha;
	int tmp=0;
	do{
		system("cls");
		printf("\n\n%s\n",nQ[n].Q);
		if(nQ[n].isq==1)
		{
			printf("\t%s\n",nQ[n].A1);
			printf("\t%s\n",nQ[n].A2);
			printf("\t%s\n",nQ[n].A3);
			printf("\t%s\n",nQ[n].A4);
		
			printf("�п�ܡG");
			
			cha=getche();
			n=nQ[n].next[chans(cha)-1];
		}
	}while(nQ[n].isq==1);
		system("cls");
		printf("\n\n%s\n\n\n",nQ[n].Q);
		system("pause");
}


/*************�P�_���*********************/
int chans(char input)
{
	switch(input)
	{
		case 'A':
		case 'a':
		case '1':
			return 1;
			break;
		case 'B':
		case 'b':
		case '2':
			return 2;
			break;
		case 'C':
		case 'c':
		case '3':
			return 3;
			break;
		case 'D':
		case 'd':
		case '4':
			return 4;
			break;
		default:
			printf("��ܿ��~,�Э��s���:");
			char cha;
			cha=getche();
			return chans(cha);
	}
}
