#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <stdint.h> // For uint8_t and uint32_t

// stats: 9-gram beijinghouse v7: https://drive.proton.me/urls/E3FXCCVK5M#vZxvy1ZK94XN (15.4 GB download -- 88.8 GB ram)

// compressed: 16543293071 bytes
// uncompressed: 52947605600 bytes
// md5 459a6fe9cc83d91e9570c53c6640a4c2
// sha1 8fa036c3a73ecd77b755f2ac466f42657a84d5e0

// input data unknown, but suggested at https://github.com/louiehelm/azdecrypt/tree/main/AZdecrypt/N-grams
// Jarlve's n-gram files draws heavily upon the collection of language data at:
// https://wortschatz.uni-leipzig.de/en/usage
// https://creativecommons.org/licenses/by-nc/4.0/

// linked from https://github.com/louiehelm/azdecrypt/tree/main

// global variables for lookup

uint32_t *g53, *g54;
    uint8_t 
**gxa9, **gxb9, **gxc9, **gxd9, **gxe9, **gxf9, **gxg9, **gxh9, **gxi9, **gxj9, **gxk9, **gxl9, **gxm9, 
**gxn9, **gxo9, **gxp9, **gxq9, **gxr9, **gxs9, **gxt9, **gxu9, **gxv9, **gxw9, **gxx9, **gxy9, **gxz9;

uint8_t bh9(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t h, uint8_t i) ;

int main() {
unsigned char* fileData3; // Temporary storage for encoder table read-in
unsigned int tablecount[256]; // Temporary storage for encoder scoring table sizes
unsigned int ngram_mem = 0;
unsigned int top_pivot, pivot, d1, d2, d3, d4, max_count, buf_len_s, acu_len_s, hop_len_s;
uint32_t encoder_count;
unsigned char fd[65535*4+65535*4+255*4];
//unsigned int highgram; // Assuming ngram_size is defined elsewhere

    int ngram_count = 0;
    pivot = 65;
    top_pivot = pivot + 26;
    ngram_mem += 2 * 4 * 26*26*26*26*26;

    g53 = calloc(26*26*26*26*26,4); // indexing 0 to 65535? or more?
    g54 = calloc(26*26*26*26*26,4);
    
    // Open gzip file
    gzFile gzf = gzopen("9-grams_english_beijinghouse_10TB_v7.txt.gz", "rb");

    //while (pivot < 68) { // this line for testing just A to C
    while (pivot < top_pivot) {
 
	uint32_t encoder_count; 	
        buf_len_s = 0;
        
        // Read and process data...
        gzread(gzf, fd, 4); // file, buffer, len
        //highgram = fd[2 + buf_len_s]; // Adjust according to actual ngram_size
        acu_len_s += 4;

        gzread(gzf, fd, 4); 
	d1 = (fd[0] << 24) + (fd[1] << 16) + (fd[2] << 8) + fd[3];
        gzread(gzf, fd, 4);
	d3 = (fd[0] << 24) + (fd[1] << 16) + (fd[2] << 8) + fd[3];
        gzread(gzf, fd, d1*4); // d1*4 bytes - e.g. with "A" it's 65535*4 = 262,040 bytes

	encoder_count= 1;
        while (encoder_count <= d1) {
fflush(stdout);
		g53[26*26*26*26*(fd[0+buf_len_s]-'A')+26*26*26*(fd[1+buf_len_s]-'A')+26*26*(fd[2+buf_len_s]-'A')+26*(fd[3+buf_len_s]-'A')+pivot-'A'] = encoder_count;
		acu_len_s += 4;
		buf_len_s += 4;
		encoder_count += 1;
	}

	buf_len_s = 0;
        gzread(gzf, fd, d3*4); // d1*4 bytes - e.g. with "A" it's 65535*4 = 262,040 bytes
	
	encoder_count = 1048576 + 1;
        while (encoder_count <= d3+1048576) {
		g53[26*26*26*26*(fd[0+buf_len_s]-'A')+26*26*26*(fd[1+buf_len_s]-'A')+26*26*(fd[2+buf_len_s]-'A')+26*(fd[3+buf_len_s]-'A')+pivot-'A'] = encoder_count;
		acu_len_s += 4;
		buf_len_s += 4;
		encoder_count += 1;
	}

	buf_len_s = 0;
        gzread(gzf, fd, 4); 
	d2 = (fd[0] << 24) + (fd[1] << 16) + (fd[2] << 8) + fd[3];
        gzread(gzf, fd, 4);
	d4 = (fd[0] << 24) + (fd[1] << 16) + (fd[2] << 8) + fd[3];
        gzread(gzf, fd, d2*4+d4*4+255*4); // d1*4 bytes - e.g. with "A" it's 65535*4 = 262,040 bytes

	encoder_count= 1;
        while (encoder_count <= d2) {
		g54[26*26*26*26*(pivot-'A')+26*26*26*(fd[0+buf_len_s]-'A')+26*26*(fd[1+buf_len_s]-'A')+26*(fd[2+buf_len_s]-'A')+(fd[3+buf_len_s]-'A')] = encoder_count;
		acu_len_s += 4;
		buf_len_s += 4;
		encoder_count += 1;
	}

	//buf_len_s = 0;
        //gzread(gzf, fd, d3*4); // d1*4 bytes - e.g. with "A" it's 65535*4 = 262,040 bytes
	
	encoder_count = 1048576 + 1;
        while (encoder_count <= d4+1048576) {
		g54[26*26*26*26*(pivot-'A')+26*26*26*(fd[0+buf_len_s]-'A')+26*26*(fd[1+buf_len_s]-'A')+26*(fd[2+buf_len_s]-'A')+(fd[3+buf_len_s]-'A')] = encoder_count;
		acu_len_s += 4;
		buf_len_s += 4;
		encoder_count += 1;
	}

	max_count = 0;

	for (int i = 255; i > 0; i--)
	{
		tablecount[i] = (fd[0+buf_len_s] << 24) + (fd[1+buf_len_s] << 16) + (fd[2+buf_len_s] << 8) + fd[3+buf_len_s];
                if (tablecount[i] > max_count) max_count = tablecount[i];
                acu_len_s += 4;
                buf_len_s += 4;
	}

	fileData3 = malloc(max_count*4); // 4 bytes for max_count
	if (!fileData3) { printf("fd3 malloc failed\n"); exit(1); }
        
        // Also, ensure proper memory allocation for arrays like g53, g54

        // Dynamic array allocation or resizing based on pivot value
        switch(pivot-65) {
        case 0: gxa9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxa9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 1: gxb9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxb9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 2: gxc9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxc9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 3: gxd9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxd9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 4: gxe9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxe9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 5: gxf9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxf9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 6: gxg9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxg9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 7: gxh9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxh9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 8: gxi9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxi9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 9: gxj9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxj9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 10: gxk9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxk9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 11: gxl9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxl9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 12: gxm9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxm9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 13: gxn9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxn9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 14: gxo9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxo9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 15: gxp9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxp9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 16: gxq9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxq9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 17: gxr9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxr9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 18: gxs9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxs9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 19: gxt9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxt9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 20: gxu9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxu9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 21: gxv9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxv9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 22: gxw9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxw9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 23: gxx9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxx9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 24: gxy9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxy9[i] = malloc(d2 * sizeof(uint8_t));  break;
        case 25: gxz9 = malloc(d1 * sizeof(uint8_t*)); for (int i = 0; i < d1; i++) gxz9[i] = malloc(d2 * sizeof(uint8_t));  break;
        }

	for (int i = 255; i >= 1; i--) {
	int j,x1,x2;
        hop_len_s = tablecount[i];
        if (hop_len_s > 0) {
            buf_len_s = 0;
            j=gzread(gzf, fileData3, hop_len_s * 4);

            if (i > 3) {
                j = i >> 2;
            } else {
                switch (i) {
                    case 3: j = 64; break;
                    case 2: j = 65; break;
                    case 1: j = 66; break;
                }
            }

		int solvesub_ngramlogcutoff = 0;
            if (j > solvesub_ngramlogcutoff) {
                while (buf_len_s < hop_len_s) {
                    x1 = (fileData3[buf_len_s] << 8) + fileData3[hop_len_s + buf_len_s] - 1;
                    x2 = (fileData3[2 * hop_len_s + buf_len_s] << 8) + fileData3[3 * hop_len_s + buf_len_s] - 1;

                    switch (pivot - 65) {
                         case 0: gxa9[x1][x2] = i; break;
                         case 1: gxb9[x1][x2] = i; break;
                         case 2: gxc9[x1][x2] = i; break;
                         case 3: gxd9[x1][x2] = i; break;
                         case 4: gxe9[x1][x2] = i; break;
                         case 5: gxf9[x1][x2] = i; break;
                         case 6: gxg9[x1][x2] = i; break;
                         case 7: gxh9[x1][x2] = i; break;
                         case 8: gxi9[x1][x2] = i; break;
                         case 9: gxj9[x1][x2] = i; break;
                         case 10: gxk9[x1][x2] = i; break;
                         case 11: gxl9[x1][x2] = i; break;
                         case 12: gxm9[x1][x2] = i; break;
                         case 13: gxn9[x1][x2] = i; break;
                         case 14: gxo9[x1][x2] = i; break;
                         case 15: gxp9[x1][x2] = i; break;
                         case 16: gxq9[x1][x2] = i; break;
                         case 17: gxr9[x1][x2] = i; break;
                         case 18: gxs9[x1][x2] = i; break;
                         case 19: gxt9[x1][x2] = i; break;
                         case 20: gxu9[x1][x2] = i; break;
                         case 21: gxv9[x1][x2] = i; break;
                         case 22: gxw9[x1][x2] = i; break;
                         case 23: gxx9[x1][x2] = i; break;
                         case 24: gxy9[x1][x2] = i; break;
                         case 25: gxz9[x1][x2] = i; break;
                    }

                    //if (j < ngram_lowval) ngram_lowval = j;
                    //if (j > ngram_highval) ngram_highval = j;
                    //ngram_values[j] += 1;

                    ngram_count++;
                    buf_len_s++;
                    acu_len_s += 4;
                }
            }
        
	}

	

        // More code...

    }
    free(fileData3);
        pivot++;

    // Clean up: close files, free allocated memory, etc.
    // Free other dynamically allocated memory

}
    gzclose(gzf);
}

// Assuming external definitions for g53, g54, gxa9, gxb9, etc.
// and their corresponding types and dimensions

uint8_t bh9(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t h, uint8_t i) 
{
    uint8_t z = 0, z_offset = 0;
    uint32_t z1, z2;

    z1 = g53[26*26*26*26*a+26*26*26*b+26*26*c+26*d+e];
    if (z1 == 0) return 0;
    z2 = g54[26*26*26*26*e+26*26*26*f+26*26*g+26*h+i];
    if (z2 == 0) return 0;

    if ((z1 & 0x100000) > 0) {
        z_offset += 1;
        z1 -= 0x100000;
    }
    if ((z2 & 0x100000) > 0) {
        z_offset += 2;
        z2 -= 0x100000;
    }

    z1--; z2--; // C adjustment

    // Adjust these lines according to how the arrays like gxa9, gxb9, etc., are defined and used
    switch (e) {
        case 0: z = gxa9[z1][z2]; break;
        case 1: z = gxb9[z1][z2]; break;
        case 2: z = gxc9[z1][z2]; break;
        case 3: z = gxd9[z1][z2]; break;
        case 4: z = gxe9[z1][z2]; break;
        case 5: z = gxf9[z1][z2]; break;
        case 6: z = gxg9[z1][z2]; break;
        case 7: z = gxh9[z1][z2]; break;
        case 8: z = gxi9[z1][z2]; break;
        case 9: z = gxj9[z1][z2]; break;
        case 10: z = gxk9[z1][z2]; break;
        case 11: z = gxl9[z1][z2]; break;
        case 12: z = gxm9[z1][z2]; break;
        case 13: z = gxn9[z1][z2]; break;
        case 14: z = gxo9[z1][z2]; break;
        case 15: z = gxp9[z1][z2]; break;
        case 16: z = gxq9[z1][z2]; break;
        case 17: z = gxr9[z1][z2]; break;
        case 18: z = gxs9[z1][z2]; break;
        case 19: z = gxt9[z1][z2]; break;
        case 20: z = gxu9[z1][z2]; break;
        case 21: z = gxv9[z1][z2]; break;
        case 22: z = gxw9[z1][z2]; break;
        case 23: z = gxx9[z1][z2]; break;
        case 24: z = gxy9[z1][z2]; break;
        case 25: z = gxz9[z1][z2]; break;
        default: break;
    }

    if (z > 0) {
        if (z_offset == (z & 0x3)) {
            z = z >> 2; // Correct quartile, shift quartile designation away to recover true score
        } else {
            if ((z_offset == 0) && (z < 4)) { // Special value to extend range above 63 in main quadrant only
                if (z == 3) z = 64;
                else if (z == 2) z = 65;
                else if (z == 1) z = 66;
            } else {
                z = 0; // Ignore scores in wrong quartiles
            }
        }
    }

    return z;
}

