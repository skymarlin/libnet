// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Chat.proto

#include "Chat.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
#include "google/protobuf/generated_message_tctable_impl.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace skymarlin {
namespace protocol {
namespace chat {

inline constexpr Chat::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : user_id_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        message_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR Chat::Chat(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct ChatDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ChatDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~ChatDefaultTypeInternal() {}
  union {
    Chat _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ChatDefaultTypeInternal _Chat_default_instance_;
}  // namespace chat
}  // namespace protocol
}  // namespace skymarlin
static ::_pb::Metadata file_level_metadata_Chat_2eproto[1];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_Chat_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_Chat_2eproto = nullptr;
const ::uint32_t TableStruct_Chat_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(
    protodesc_cold) = {
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::skymarlin::protocol::chat::Chat, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::skymarlin::protocol::chat::Chat, _impl_.user_id_),
    PROTOBUF_FIELD_OFFSET(::skymarlin::protocol::chat::Chat, _impl_.message_),
};

static const ::_pbi::MigrationSchema
    schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::skymarlin::protocol::chat::Chat)},
};

static const ::_pb::Message* const file_default_instances[] = {
    &::skymarlin::protocol::chat::_Chat_default_instance_._instance,
};
const char descriptor_table_protodef_Chat_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n\nChat.proto\022\027skymarlin.protocol.chat\"(\n"
    "\004Chat\022\017\n\007user_id\030\001 \001(\t\022\017\n\007message\030\002 \001(\tb"
    "\006proto3"
};
static ::absl::once_flag descriptor_table_Chat_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_Chat_2eproto = {
    false,
    false,
    87,
    descriptor_table_protodef_Chat_2eproto,
    "Chat.proto",
    &descriptor_table_Chat_2eproto_once,
    nullptr,
    0,
    1,
    schemas,
    file_default_instances,
    TableStruct_Chat_2eproto::offsets,
    file_level_metadata_Chat_2eproto,
    file_level_enum_descriptors_Chat_2eproto,
    file_level_service_descriptors_Chat_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_Chat_2eproto_getter() {
  return &descriptor_table_Chat_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_Chat_2eproto(&descriptor_table_Chat_2eproto);
namespace skymarlin {
namespace protocol {
namespace chat {
// ===================================================================

class Chat::_Internal {
 public:
};

Chat::Chat(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:skymarlin.protocol.chat.Chat)
}
inline PROTOBUF_NDEBUG_INLINE Chat::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : user_id_(arena, from.user_id_),
        message_(arena, from.message_),
        _cached_size_{0} {}

Chat::Chat(
    ::google::protobuf::Arena* arena,
    const Chat& from)
    : ::google::protobuf::Message(arena) {
  Chat* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);

  // @@protoc_insertion_point(copy_constructor:skymarlin.protocol.chat.Chat)
}
inline PROTOBUF_NDEBUG_INLINE Chat::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : user_id_(arena),
        message_(arena),
        _cached_size_{0} {}

inline void Chat::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
}
Chat::~Chat() {
  // @@protoc_insertion_point(destructor:skymarlin.protocol.chat.Chat)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void Chat::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.user_id_.Destroy();
  _impl_.message_.Destroy();
  _impl_.~Impl_();
}

PROTOBUF_NOINLINE void Chat::Clear() {
// @@protoc_insertion_point(message_clear_start:skymarlin.protocol.chat.Chat)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.user_id_.ClearToEmpty();
  _impl_.message_.ClearToEmpty();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* Chat::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<1, 2, 0, 51, 2> Chat::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    2, 8,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967292,  // skipmap
    offsetof(decltype(_table_), field_entries),
    2,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_Chat_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
  }, {{
    // string message = 2;
    {::_pbi::TcParser::FastUS1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(Chat, _impl_.message_)}},
    // string user_id = 1;
    {::_pbi::TcParser::FastUS1,
     {10, 63, 0, PROTOBUF_FIELD_OFFSET(Chat, _impl_.user_id_)}},
  }}, {{
    65535, 65535
  }}, {{
    // string user_id = 1;
    {PROTOBUF_FIELD_OFFSET(Chat, _impl_.user_id_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // string message = 2;
    {PROTOBUF_FIELD_OFFSET(Chat, _impl_.message_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\34\7\7\0\0\0\0\0"
    "skymarlin.protocol.chat.Chat"
    "user_id"
    "message"
  }},
};

::uint8_t* Chat::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:skymarlin.protocol.chat.Chat)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // string user_id = 1;
  if (!this->_internal_user_id().empty()) {
    const std::string& _s = this->_internal_user_id();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "skymarlin.protocol.chat.Chat.user_id");
    target = stream->WriteStringMaybeAliased(1, _s, target);
  }

  // string message = 2;
  if (!this->_internal_message().empty()) {
    const std::string& _s = this->_internal_message();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "skymarlin.protocol.chat.Chat.message");
    target = stream->WriteStringMaybeAliased(2, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:skymarlin.protocol.chat.Chat)
  return target;
}

::size_t Chat::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:skymarlin.protocol.chat.Chat)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string user_id = 1;
  if (!this->_internal_user_id().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_user_id());
  }

  // string message = 2;
  if (!this->_internal_message().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_message());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::google::protobuf::Message::ClassData Chat::_class_data_ = {
    Chat::MergeImpl,
    nullptr,  // OnDemandRegisterArenaDtor
};
const ::google::protobuf::Message::ClassData* Chat::GetClassData() const {
  return &_class_data_;
}

void Chat::MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg) {
  auto* const _this = static_cast<Chat*>(&to_msg);
  auto& from = static_cast<const Chat&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:skymarlin.protocol.chat.Chat)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_user_id().empty()) {
    _this->_internal_set_user_id(from._internal_user_id());
  }
  if (!from._internal_message().empty()) {
    _this->_internal_set_message(from._internal_message());
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void Chat::CopyFrom(const Chat& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:skymarlin.protocol.chat.Chat)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool Chat::IsInitialized() const {
  return true;
}

::_pbi::CachedSize* Chat::AccessCachedSize() const {
  return &_impl_._cached_size_;
}
void Chat::InternalSwap(Chat* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.user_id_, &other->_impl_.user_id_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.message_, &other->_impl_.message_, arena);
}

::google::protobuf::Metadata Chat::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Chat_2eproto_getter, &descriptor_table_Chat_2eproto_once,
      file_level_metadata_Chat_2eproto[0]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace chat
}  // namespace protocol
}  // namespace skymarlin
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"