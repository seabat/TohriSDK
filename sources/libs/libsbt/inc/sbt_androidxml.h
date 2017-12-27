
/*
 * [Desccription]
 * Get a number of array items   
 *
 * <resources>
 *     <string-array name="planets_array">
 *         <item>Mercury</item>
 *         <item>Venus</item>
 *         <item>Earth</item>
 *         <item>Mars</item>
 *     </string-array>
 * </resources>
 *   
 */
int sbt_androidxml_get_array_length(const char* file_name, const char* res_name);  

/*
 * [Desccription]
 * Get array items spcified string 
 *
 * <resources>
 *     <string-array name="planets_array">
 *         <item>Mercury</item>
 *         <item>Venus</item>
 *         <item>Earth</item>
 *         <item>Mars</item>
 *     </string-array>
 * </resources>
 *
 * char[][]= {  "Mercury", 
 *              "Venus", 
 *              "Earth",
 *              "Mars"
 * };
 *       
 */
char* sbt_androidxml_get_string_array(const char* file_name, const char* res_name);  

/*
 * [Desccription]
 * Get array items spcified interger 
 *
 * <resources>
 *     <integer-array name="sample_ids">
 *         <item>1</item>
 *         <item>2</item>
 *         <item>3</item>
 *     </integer-array>
 * </resources>
 */
int* sbt_androidxml_get_int_array(const char* file_name, const char* res_name);  


void test_sbt_androidxml();
