#include <elf.h>
#include <stdio.h>

int main(int argc, char** argv){

  printf("DEBUG: we have %d args first arg is %s (should be a file name)\n",argc, argv[1]);
  
  Elf32_Ehdr header;
  size_t status;
  FILE* fin;
  char buf[1];
  int i;
  
  fin = fopen(argv[1], "r");
  if (!fin) return 1;
  status = fread(&header, sizeof(header),1 ,fin);
  
  //Architecture  is 32bit
  printf("this program support only Intel 80386 machines\n");
  if (header.e_machine != 3) return 2;
  
  printf("Magic Number:\t");
  for (i=0; i<8;i++)
    printf("%x " ,header.e_ident[i]);
  printf("\n");
  
  switch(header.e_type){
    case 0:
      printf("ET_NONE 0 No file type\n");
      break;
    case 1:
      printf("ET_REL 1 Relocatable file\n");
      break;
    case 2:
      printf("ET_EXEC 2 Executable file\n"); 
      break;
    case 3:
      printf("ET_DYN 3 Shared object file\n"); 
      break;
    case 4:
      printf("ET_CORE 4 Core file\n"); 
      break;   
    default:
      printf("e_type is  %d (UNKNOWN) /* Object file type */\n", header.e_type);
  }
  
  
  /*
   * 
   * e_ident
__ _____P__o_s_it_io__n_ _____________V__a_lu__e____
		e_ident[EI_CLASS] ELFCLASS32
		e_ident[EI_DATA] ELFDATA2LSB
/*
 * 
 * 
  //printf("e_type is  %d /* Object file type */\n", header.e_type);
  printf("e_machine is  %d /* Architecture */\n", header.e_machine);
  printf("e_version is  %d /* Object file version */\n", header.e_version);
  printf("e_entry is  %d /* Entry point virtual address */\n", header.e_entry);
  printf("e_phoff is  %d /* Program header table file offset */\n", header.e_phoff);
  printf("e_shoff is  %d /* Section header table file offset */\n", header.e_shoff);
  printf("e_flags is  %d /* Processor-specific flags */\n", header.e_flags);
  printf("e_ehsize is  %d /* ELF header size in bytes */\n", header.e_ehsize);
  printf("e_phentsize is  %d /* Program header table entry size */\n", header.e_phentsize);
  printf("e_phnum is  %d /* Program header table entry count */\n", header.e_phnum);
  printf("e_shentsize is  %d /* Section header table entry size */\n", header.e_shentsize);
  printf("e_shnum is  %d /* Section header table entry count */\n", header.e_shnum);
  printf("e_shstrndx is  %d /* Section header string table index */\n", header.e_shstrndx);

  fseek(fin, header.e_shoff + header.e_shstrndx * header.e_shentsize, SEEK_SET);
  Elf32_Shdr section_header;
  status = fread(&section_header, sizeof(section_header),1 ,fin);
  
  i=0;
  
  while (i<1){
    printf("sh_name %d /* Section name (string tbl index) */\n", section_header.sh_name);
    printf("sh_type %d /* Section type */\n", section_header.sh_type);
    printf("sh_flags %d /* Section flags */\n", section_header.sh_flags);
    printf("sh_addr %d /* Section virtual addr at execution */\n", section_header.sh_addr);
    printf("sh_offset %d /* Section file offset */\n", section_header.sh_offset);
    printf("sh_size %d /* Section size in bytes */\n", section_header.sh_size);
    printf("sh_link %d /* Link to another section */\n", section_header.sh_link);
    printf("sh_info %d /* Additional section information */\n", section_header.sh_info);
    printf("sh_addralign %d /* Section alignment */\n", section_header.sh_addralign);
    printf("sh_entsize %d /* Entry size if section holds table */\n", section_header.sh_entsize);
    
    fseek(fin, sizeof(section_header), SEEK_CUR);
    status = fread(&section_header, sizeof(section_header),1 ,fin);
    i++;
  }
  
  

  fclose(fin);
  return 0;
}