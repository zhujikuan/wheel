#include <json-c/json.h>
#include <stdio.h>
void json_object_print_type(json_object *obj, const char *key) {
    json_type type;

    type = json_object_get_type(obj); /*Getting the type of the json object*/
    switch (type) {
        case json_type_null:
            printf("%s is json_type_null\n", key);
            printf("          value: %s\n", json_object_get_string(obj));
            break;

        case json_type_boolean:
            printf("%s is json_type_boolean\n", key);
            printf("          value: %s\n",
                   json_object_get_boolean(obj) ? "true" : "false");
            break;

        case json_type_double:
            printf("%s is json_type_double\n", key);
            printf("          value: %lf\n", json_object_get_double(obj));
            break;

        case json_type_int:
            printf("%s is json_type_int\n", key);
            printf("          value: %d\n", json_object_get_int(obj));
            break;

        case json_type_object:
            printf("%s is json_type_object\n", key);
            printf("          value: %s\n", json_object_get_string(obj));
            break;

        case json_type_array:
            printf("%s is json_type_array\n", key);
            printf("          value: %s\n", json_object_get_string(obj));
            break;

        case json_type_string:
            printf("%s is json_type_string\n", key);
            printf("          value: %s\n", json_object_get_string(obj));
            break;

        default:
            printf("%s: WTF, unhandled case, type %d\n", key, type);
            printf("          value: %s\n", json_object_get_string(obj));
    }
}
int main(void) {
    json_object *root = json_object_from_file("hello.json");
    if (!root) return 1;

    json_object *first_name = json_object_object_get(root, "person");
    json_object *lua_script = json_object_object_get(root, "lua_script");
    printf("%s\n", json_object_get_string(lua_script));
    json_object_print_type(root, "root");
    json_object_print_type(first_name, "person");
    json_object_print_type(lua_script, "lua_script");

    json_object_put(root);
    return 0;
}