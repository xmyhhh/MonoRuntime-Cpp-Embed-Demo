#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
#include <string>

struct Component
{
	int id;
	int tag;
};

Component* Components;
uint32_t num_Components;
MonoClassField* native_handle_field;
MonoDomain* domain;
MonoClass* Component_class;
//获取属性
int ManagedLibrary_Component_get_id_Internal(const Component* component)
{
	return component->id;
}

int ManagedLibrary_Component_get_tag(MonoObject* this_ptr)
{
	Component* component;
	mono_field_get_value(this_ptr, native_handle_field, reinterpret_cast<void*>(&component));
	return component->tag;
}
//获取组件
MonoArray* ManagedLibrary_Component_GetComponents()
{
	MonoArray* array = mono_array_new(domain, Component_class, num_Components);

	for (uint32_t i = 0; i < num_Components; ++i)
	{
		MonoObject* obj = mono_object_new(domain, Component_class);
		mono_runtime_object_init(obj);
		void* native_handle_value = &Components[i];
		mono_field_set_value(obj, native_handle_field, &native_handle_value);
		mono_array_set(array, MonoObject*, i, obj);
	}

	return array;
}

int main(int argc, const char* argv[])
{
	// 设置搜索路径，用于搜索mscorlib.dll
	std::string MonoPath = "../dependency/mono";
	std::string monoLibPath = MonoPath + "/lib";
	std::string monoEtcPath = MonoPath + "/etc";
	mono_set_dirs(monoLibPath.c_str(), monoEtcPath.c_str());
	mono_config_parse(NULL);

	//获取应用域 
	const char* managed_binary_path = "MainTest.dll";
	domain = mono_jit_init(managed_binary_path);

	//加载程序集MainTest.dll
	MonoAssembly* assembly = mono_domain_assembly_open(domain, managed_binary_path);
	MonoImage* image = mono_assembly_get_image(assembly);

	// 注册函数，这里是以后主要添加的地方 ，所有的函数都是通过该方法绑定的
	mono_add_internal_call("ManagedLibrary.Component::get_id_Internal", reinterpret_cast<void*>(ManagedLibrary_Component_get_id_Internal));
	mono_add_internal_call("ManagedLibrary.Component::get_Tag", reinterpret_cast<void*>(ManagedLibrary_Component_get_tag));
	mono_add_internal_call("ManagedLibrary.Component::GetComponents", reinterpret_cast<void*>(ManagedLibrary_Component_GetComponents));
	Component_class = mono_class_from_name(image, "ManagedLibrary", "Component");
	native_handle_field = mono_class_get_field_from_name(Component_class, "native_handle");

	num_Components = 5;
	Components = new Component[5];
	for (uint32_t i = 0; i < num_Components; ++i)
	{
		Components[i].id = i;
		Components[i].tag = i * 4;
	}

	MonoClass* main_class = mono_class_from_name(image, "ManagedLibrary", "Main");

	const bool include_namespace = true;
	MonoMethodDesc* managed_method_desc = mono_method_desc_new("ManagedLibrary.Main:TestComponent()", include_namespace);
	MonoMethod* managed_method = mono_method_desc_search_in_class(managed_method_desc, main_class);
	mono_method_desc_free(managed_method_desc);
	mono_runtime_invoke(managed_method, NULL, NULL, NULL);

	//清理mono环境
	mono_jit_cleanup(domain);

	delete[] Components;
	return 0;
}
