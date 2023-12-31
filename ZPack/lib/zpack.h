#ifndef __ZPACK_H__
#define __ZPACK_H__

/** @file */

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#ifdef zpack_EXPORTS // Defined by CMake
#   if defined(_WIN32) || defined(__CYGWIN__) || defined(__ORBIS__)
#       define ZPACK_EXPORT __declspec(dllexport)
#   else
#       define ZPACK_EXPORT
#   endif
#else
#   define ZPACK_EXPORT
#endif

#define ZPACK_VERSION_MAJOR 2
#define ZPACK_VERSION_MINOR 0
#define ZPACK_VERSION_PATCH 3
#define ZPACK_VERSION (ZPACK_VERSION_MAJOR * 100000 + ZPACK_VERSION_MINOR * 1000 + ZPACK_VERSION_PATCH * 10)
#define ZPACK_VERSION_STRING "2.0.3"

typedef uint8_t  zpack_u8;
typedef uint16_t zpack_u16;
typedef uint32_t zpack_u32;
typedef uint64_t zpack_u64;

typedef zpack_u8 zpack_bool;
#define ZPACK_FALSE 0
#define ZPACK_TRUE 1

// file format details
#define ZPACK_HEADER_SIGNATURE 0x154b505a // ZPK\x15
#define ZPACK_DATA_SIGNATURE   0x144b505a // ZPK\x14
#define ZPACK_CDR_SIGNATURE    0x134b505a // ZPK\x13
#define ZPACK_EOCDR_SIGNATURE  0x124b505a // ZPK\x12

#define ZPACK_SIGNATURE_SIZE 4
#define ZPACK_HEADER_SIZE 6
#define ZPACK_CDR_HEADER_SIZE 20
#define ZPACK_FILE_ENTRY_FIXED_SIZE 35 // size of fixed fields in file entry
#define ZPACK_EOCDR_SIZE 12
#define ZPACK_MINIMUM_ARCHIVE_SIZE (ZPACK_HEADER_SIZE + ZPACK_SIGNATURE_SIZE + ZPACK_CDR_HEADER_SIZE + ZPACK_EOCDR_SIZE)

#define ZPACK_MAX_FILENAME_LENGTH 65535

// archive versions supported
#define ZPACK_ARCHIVE_VERSION_MIN 1
#define ZPACK_ARCHIVE_VERSION_MAX 1

/** @defgroup common Common
 */

/**
 * @ingroup common
 */
typedef enum zpack_compression_method_e
{
    ZPACK_COMPRESSION_NONE = 0,
    ZPACK_COMPRESSION_ZSTD = 1,
    ZPACK_COMPRESSION_LZ4  = 2

} zpack_compression_method;

/**
 * @ingroup common
 */
typedef struct zpack_file_entry_s
{
    char*     filename;
    zpack_u64 offset;
    zpack_u64 comp_size;
    zpack_u64 uncomp_size;
    zpack_u64 hash;
    zpack_u8  comp_method;
    
} zpack_file_entry;

/**
 * @ingroup reader
 */
typedef struct zpack_reader_s
{
    zpack_u16 version;
    zpack_file_entry* file_entries;
    zpack_u64 file_count;
    zpack_u64 comp_size;
    zpack_u64 uncomp_size;
    size_t file_size;

    // zstd
    void* zstd_dctx;

    // LZ4
    void* lz4f_dctx;

    size_t last_return; // last compression library return value

    // offsets
    zpack_u64 cdr_offset;
    zpack_u64 eocdr_offset;

    zpack_u8* buffer;
    zpack_bool buffer_shared;
    FILE* file;

} zpack_reader;

/**
 * @ingroup writer
 */
typedef struct zpack_compress_options_s
{
    zpack_compression_method method;
    int level;

} zpack_compress_options;

/**
 * @ingroup writer
 */
typedef struct zpack_file_s
{
    char*     filename;
    zpack_u8* buffer;
    zpack_u64 size;

    zpack_compress_options* options;
    void* cctx;

} zpack_file;

/**
 * @ingroup writer
 */
typedef struct zpack_writer_s
{
    zpack_u8* buffer;
    size_t buffer_capacity;
    FILE* file;
    size_t file_size;

    size_t write_offset;

    zpack_file_entry* file_entries;
    zpack_u64 fe_capacity;
    zpack_u64 file_count;

    // zstd
    void* zstd_cctx;
    
    // LZ4
    void* lz4f_cctx;

    size_t last_return; // last compression library return value

    // offsets
    zpack_u64 cdr_offset;
    zpack_u64 eocdr_offset;

} zpack_writer;

/**
 * @ingroup stream
 */
typedef struct zpack_stream_s
{
    zpack_u8* next_in; //!< Input buffer
    size_t avail_in; //!< Size of the input buffer
    size_t total_in; //!< Total bytes read

    zpack_u8* next_out; //!< Input buffer
    size_t avail_out; //!< Size of the input buffer
    size_t total_out; //!< Total bytes written

    size_t read_back; //!< Amount of bytes (starting from the end of the current input buffer) that needs to be present for the next operation. The data is expected to be at the beginning of the next input buffer

    // xxHash
    void* xxh3_state; 

} zpack_stream;

/**
 * @ingroup common
 */
enum zpack_result //! Return codes
{
    ZPACK_OK,                         //!< No errors

    ZPACK_ERROR_ARCHIVE_NOT_LOADED,   //!< Archive has not been loaded
    ZPACK_ERROR_WRITER_NOT_OPENED,    //!< Writer has not been opened
    ZPACK_ERROR_OPEN_FAILED,          //!< Failed to open file
    ZPACK_ERROR_SEEK_FAILED,          //!< Failed to seek file
    ZPACK_ERROR_FILE_TOO_SMALL,       //!< File size too small to be an archive
    ZPACK_ERROR_SIGNATURE_INVALID,    //!< Invalid archive signature
    ZPACK_ERROR_READ_FAILED,          //!< Failed to read data from the archive
    ZPACK_ERROR_BLOCK_SIZE_INVALID,   //!< Invalid block size
    ZPACK_ERROR_VERSION_INCOMPATIBLE, //!< Archive version is not supported
    ZPACK_ERROR_MALLOC_FAILED,        //!< Failed to allocate memory
    ZPACK_ERROR_FILE_NOT_FOUND,       //!< Could not find file in archive
    ZPACK_ERROR_BUFFER_TOO_SMALL,     //!< Buffer size is too small
    ZPACK_ERROR_DECOMPRESS_FAILED,    //!< Decompression error (check last_return for the compression library's error code)
    ZPACK_ERROR_COMPRESS_FAILED,      //!< Compression error (check last_return for the compression library's error code)
    ZPACK_ERROR_FILE_HASH_MISMATCH,   //!< The decompressed file's hash does not match the original file's hash
    ZPACK_ERROR_FILE_OFFSET_INVALID,  //!< Invalid file offset
    ZPACK_ERROR_FILE_INCOMPLETE,      //!< The file's data is incomplete
    ZPACK_ERROR_FILE_SIZE_INVALID,    //!< Invalid file size
    ZPACK_ERROR_COMP_METHOD_INVALID,  //!< Invalid compression method
    ZPACK_ERROR_WRITE_FAILED,         //!< Failed to write data to file
    ZPACK_ERROR_STREAM_INVALID,       //!< Invalid stream
    ZPACK_ERROR_HASH_FAILED,          //!< Failed to generate hash for the data provided
	ZPACK_ERROR_FILENAME_TOO_LONG,    //!< Filename length exceeds limit (65535 characters)
    ZPACK_ERROR_NOT_AVAILABLE         //!< Feature not available in this build of ZPack (compression method disabled, etc.)

};

#ifdef __cplusplus
extern "C" {
#endif

// Reading //

/** @defgroup lowlevel_read Low-level Reading Functions
 *  These are advanced reading functions that requires you to manage data manually.
 *  For a more conventional way to read archives, see @ref reader
 *  @{
 */

/**
 * Read the header from memory.
 * @param buffer The buffer to read from.
 * @param version Version of the archive.
 */
ZPACK_EXPORT int zpack_read_header_memory(const zpack_u8* buffer, zpack_u16* version);

/**
 * Read the header from a file stream.
 * @param fp The file to read from.
 * @param version Version of the archive.
 */
ZPACK_EXPORT int zpack_read_header(FILE* fp, zpack_u16* version);

/**
 * Read and verify the data header from memory.
 * @param buffer The buffer to read from.
 */
ZPACK_EXPORT int zpack_read_data_header_memory(const zpack_u8* buffer);

/**
 * Read and verify the data header from a file stream.
 * @param fp The file to read from.
 */
ZPACK_EXPORT int zpack_read_data_header(FILE* fp);

/**
 * Read the end of central directory record from memory.
 * @param buffer The buffer to read from.
 * @param cdr_offset Offset of the central directory record from the start of the archive.
 */
ZPACK_EXPORT int zpack_read_eocdr_memory(const zpack_u8* buffer, zpack_u64* cdr_offset);

/**
 * Read the end of central directory record from a file stream.
 * @param fp The file to read from.
 * @param eocdr_offset Offset of the end of central directory record from the start of the archive.
 * @param cdr_offset Offset of the central directory record from the start of the archive.
 */
ZPACK_EXPORT int zpack_read_eocdr(FILE* fp, zpack_u64 eocdr_offset, zpack_u64* cdr_offset);

/**
 * Read the central directory record's header from memory. Note that this function is used
 * automatically by both zpack_read_cdr_memory and zpack_read_cdr.
 * @param buffer The buffer to read from.
 * @param count The number of file entries.
 * @param block_size Size of the entire block (excluding the header)
 * @see zpack_read_cdr_memory, zpack_read_cdr
 */
ZPACK_EXPORT int zpack_read_cdr_header_memory(const zpack_u8* buffer, zpack_u64* count, zpack_u64* block_size);

/**
 * Read a single file entry from memory. Note that this function is used automatically by both
 * zpack_read_cdr_memory and zpack_read_cdr.
 * @param buffer The buffer to read from.
 * @param size_left The size remaining of the buffer containing the block. Will be checked against
                    and subtracted by the entry size.
 * @param entry The file entry.
 * @param entry_size Size of the entry in bytes.
 * @see zpack_read_cdr_memory, zpack_read_cdr
 */
ZPACK_EXPORT int zpack_read_file_entry_memory(const zpack_u8* buffer, zpack_u64* size_left, zpack_file_entry* entry, size_t* entry_size);

/**
 * Read all file entries from memory. Note that this function is used automatically by both
 * zpack_read_cdr_memory and zpack_read_cdr.
 * @param buffer The buffer to read from.
 * @param entries The file entries.
 * @param header_count Expected number of file entries (from the header)
 * @param block_size Size of the entire block.
 * @param count Number of file entries read (0 <= count <= header_count)
 * @param total_cs The total compressed size of all files in the archive.
 * @param total_us The total uncompressed size of all files in the archive.
 * @see zpack_read_cdr_memory, zpack_read_cdr
 */
ZPACK_EXPORT int zpack_read_file_entries_memory(const zpack_u8* buffer, zpack_file_entry** entries, zpack_u64 header_count, zpack_u64 block_size, zpack_u64* count, zpack_u64* total_cs, zpack_u64* total_us);

/**
 * Read the central directory record from memory.
 * @param buffer The buffer to read from.
 * @param size_left Number of bytes left from the current buffer position. Used for bounds checking.
                    Note: This function does bounds checking by the fact that CDRs have an
                    undetermined size. Other functions requires that you do bounds checking manually.
 * @param entries The file entries.
 * @param count Number of file entries.
 * @param total_cs The total compressed size of all files in the archive.
 * @param total_us The total uncompressed size of all files in the archive.
 */
ZPACK_EXPORT int zpack_read_cdr_memory(const zpack_u8* buffer, size_t size_left, zpack_file_entry** entries, zpack_u64* count, zpack_u64* total_cs, zpack_u64* total_us);

/**
 * Read the central directory record from a file stream.
 * @param fp The file to read from.
 * @param cdr_offset Offset of the central directory record from the start of the archive.
 * @param entries The file entries.
 * @param count Number of file entries.
 * @param total_cs The total compressed size of all files in the archive.
 * @param total_us The total uncompressed size of all files in the archive.
 */
ZPACK_EXPORT int zpack_read_cdr(FILE* fp, zpack_u64 cdr_offset, zpack_file_entry** entries, zpack_u64* count, zpack_u64* total_cs, zpack_u64* total_us);

/** @} */ // lowlevel_read

/** @defgroup reader Reader
 *  The archive reader.\n
 *  Thread safety: <b>Not guaranteed.</b>\n
 *  When reading from a buffer, all file reading functions are guaranteed to be thread safe,
 *  provided that you use a different decompression context for each thread.\n
 *  When reading from a file, thread safety is not guaranteed due to separate fseek/fread operations.
 *  @{
 */

/**
 * Read the entire archive from the buffer assigned in the reader.
 * @param reader The reader.
 * @return A return code (see @ref zpack_result)
 * @see zpack_init_reader_memory, zpack_init_reader_memory_shared
 */
ZPACK_EXPORT int zpack_read_archive_memory(zpack_reader* reader);

/**
 * Read the entire archive from the file stream assigned in the reader.
 * @param reader The reader.
 * @return A return code (see @ref zpack_result)
 * @see zpack_init_reader, zpack_init_reader_cfile
 */
ZPACK_EXPORT int zpack_read_archive(zpack_reader* reader);


/**
 * Read the raw compressed data of a file.
 * @param reader The reader.
 * @param entry The file entry.
 * @param buffer The output buffer.
 * @param max_size Maximum number of bytes to read from.
 * @return A return code (see @ref zpack_result)
 * @see zpack_read_file
 */
ZPACK_EXPORT int zpack_read_raw_file(zpack_reader* reader, zpack_file_entry* entry, zpack_u8* buffer, size_t max_size);

/**
 * Read and decompress the data of a file.
 * @param reader The reader.
 * @param entry The file entry.
 * @param buffer The output buffer.
 * @param max_size Maximum number of bytes to read from.
 * @param dctx The decompression context to be used. The context's compression library must
               match the file's compression method. You can pass NULL to use the reader's
               built-in decompression contexts.
 * @return A return code (see @ref zpack_result)
 */
ZPACK_EXPORT int zpack_read_file(zpack_reader* reader, zpack_file_entry* entry, zpack_u8* buffer, size_t max_size, void* dctx);

/**
 * (Streaming) Read the raw compressed data of a file. The data will be read to the input buffer
 * (next_in) as it's intended to be decompressed to an output buffer. Reading will start from
 * entry.offset + stream.total_in (or continue from the previous operation)\n
 * next_in, avail_in and total_in will be updated to reflect the number of bytes read.
 * @param reader The reader.
 * @param entry The file entry.
 * @param stream The stream.
 * @param in_size Number of bytes read to the input buffer (0 <= in_size <= stream.avail_in)
 * @return A return code (see @ref zpack_result)
 * @see zpack_read_file_stream
 */
ZPACK_EXPORT int zpack_read_raw_file_stream(zpack_reader* reader, zpack_file_entry* entry, zpack_stream* stream, size_t* in_size);

/**
 * (Streaming) Read and decompress the data of a file. The compressed data will be read to
 * next_in, and decompressed to next_out. Reading will start from entry.offset + stream.total_in
 * (or continue from the previous operation). Call this function repeatedly until stream.total_in
 * == entry.comp_size && stream.read_back == 0, in which case the entire file has been decompressed.\n
 * The stream will be updated to reflect the number of bytes read/written.\n
 * The compressed data might not be decompressed entirely in one go, in which case stream.read_back
 * will be set. It specifies the amount of bytes needed from the current input buffer, starting
 * from the end of the buffer. This data must be present at the start of the next input buffer.
 * @param reader The reader.
 * @param entry The file entry.
 * @param stream The stream.
 * @param dctx The decompression context to be used. The context's compression library must
               match the file's compression method. You can pass NULL to use the reader's
               built-in decompression contexts.
 * @return A return code (see @ref zpack_result)
 */
ZPACK_EXPORT int zpack_read_file_stream(zpack_reader* reader, zpack_file_entry* entry, zpack_stream* stream, void* dctx);

/**
 * Initializes the reader using a file.
 * @param reader The reader.
 * @param path UTF-8 formatted path to the archive. If you're on Windows, use
               @ref zpack_convert_wchar_to_utf8 if needed.
 * @return A return code (see @ref zpack_result)
 */
ZPACK_EXPORT int zpack_init_reader(zpack_reader* reader, const char* path);

/**
 * Initializes the reader using an already opened file stream. Note that this file stream will
 * be closed by zpack_close_reader; you may set reader->file to NULL before calling it to prevent
 * the file from being closed.
 * @param reader The reader.
 * @param fp The file stream.
 * @return A return code (see @ref zpack_result)
 */
ZPACK_EXPORT int zpack_init_reader_cfile(zpack_reader* reader, FILE* fp);

/**
 * Initializes the reader using a buffer containing the archive.
 * @param reader The reader.
 * @param buffer The archive buffer.
 * @param size The size of the buffer.
 * @return A return code (see @ref zpack_result)
 */
ZPACK_EXPORT int zpack_init_reader_memory(zpack_reader* reader, const zpack_u8* buffer, size_t size);

/**
 * Same as zpack_init_reader_memory, without copying the archive buffer to another one. The data
 * will be read directly from the buffer provided and is expected to be present throughout the
 * entire reading session. Note that the buffer will not be freed by zpack_close_reader.
 * @param reader The reader.
 * @param buffer The archive buffer.
 * @param size The size of the buffer.
 * @return A return code (see @ref zpack_result)
 */
ZPACK_EXPORT int zpack_init_reader_memory_shared(zpack_reader* reader, zpack_u8* buffer, size_t size);

/**
 * Resets the reader's built-in decompression contexts. This is usually done automatically, but if
 * a reading operation was stopped prematurely, this MUST be called before starting another reading
 * operation.
 * @param reader The reader.
 */
ZPACK_EXPORT void zpack_reset_reader_dctx(zpack_reader* reader);

/**
 * Closes the reader, releasing all resources previously occupied by it. This will make the reader
 * ready to be reused for another session.
 * @param reader The reader.
 */
ZPACK_EXPORT void zpack_close_reader(zpack_reader* reader);

/** @} */ // reader

// Writing //

/** @defgroup writer Writer
 *  The archive writer.\n
 *  Thread safety: <b>Not thread safe.</b>\n
 *  Each blocks/files are expected to be written asynchronously, one after the other. Running multiple
 *  write operations at the same time will result in undefined behavior.\n
 *  Note that there are no guides or restrictions on the ordering of each block while writing the archive,
 *  so make sure to follow the correct order by yourself. (or use @ref zpack_write_archive)\n
 *  (header -> data header -> files -> cdr -> eocdr)
 *  @{
 */

/**
 * Initializes the writer and opens a file for writing.
 * @param writer The writer.
 * @param path UTF-8 formatted path to the archive. If you're on Windows, use
               @ref zpack_convert_wchar_to_utf8 if needed.
 * @return A return code (see @ref zpack_result)
 */
ZPACK_EXPORT int zpack_init_writer(zpack_writer* writer, const char* path);

/**
 * Initializes the writer and sets the output file stream to fp.
 * @param writer The writer.
 * @param fp The file stream.
 * @return A return code (see @ref zpack_result)
 */
ZPACK_EXPORT int zpack_init_writer_cfile(zpack_writer* writer, FILE* fp);

/**
 * Initializes the writer and allocates a memory heap for writing, using the initial size provided.
 * If the initial size is 0 or too small, it'll be set to the minimum archive size. The buffer will be
 * resized automatically to fit the data during write operations.
 * @param writer The writer.
 * @param initial_size The initial heap size.
 * @return A return code (see @ref zpack_result)
 */
ZPACK_EXPORT int zpack_init_writer_heap(zpack_writer* writer, size_t initial_size);


/**
 * Write the header.
 * @param writer The writer.
 */
ZPACK_EXPORT int zpack_write_header(zpack_writer* writer);

/**
 * (Ex) Write the header.\n
 * Note: If unsure, use @ref zpack_write_header instead.
 * @param writer The writer.
 * @param version The archive's version.
 * @see zpack_write_header
 */
ZPACK_EXPORT int zpack_write_header_ex(zpack_writer* writer, zpack_u16 version);

/**
 * Write the data header.
 * @param writer The writer.
 */
ZPACK_EXPORT int zpack_write_data_header(zpack_writer* writer);

/**
 * Compress and write files to archive.
 * @param writer The writer.
 * @param files Files to be written.
 * @param file_count Number of files to be written.
 */
ZPACK_EXPORT int zpack_write_files(zpack_writer* writer, zpack_file* files, zpack_u64 file_count);

/**
 * Copy files from another archive.
 * @param writer The writer.
 * @param reader The reader (for the other archive).
 * @param entries Files to be written.
 * @param file_count Number of files to be written.
 */
ZPACK_EXPORT int zpack_write_files_from_archive(zpack_writer* writer, zpack_reader* reader, zpack_file_entry* entries, zpack_u64 file_count);

/**
 * (Streaming) Compress and write (part of) file to archive.
 * Call this function repeatedly with new data, then call @ref zpack_write_file_stream_end
 * when all data has been consumed to write a file.
 * Only stream.next_in and stream.avail_in are updated after each call.
 * The output buffer only serves as a temporary buffer before the data is written to the writer's
 * output.
 * @param writer The writer.
 * @param options Compression options.
 * @param stream The stream.
 * @param cctx The compression context to be used. The context's compression library must match
               the compression method specified in options. You can pass NULL to use the writer's
               built-in compression contexts.
 */
ZPACK_EXPORT int zpack_write_file_stream(zpack_writer* writer, zpack_compress_options* options, zpack_stream* stream, void* cctx);

/**
 * (Streaming) Ends a file writing session. Flushes all data to the output and adds the file
 * into the file entry list. stream.next_in and stream.avail_in is allowed to be empty.
 * @param writer The writer.
 * @param filename Filename.
 * @param options Compression options.
 * @param stream The stream.
 * @param cctx The compression context to be used. This context must be the one used for
               @ref zpack_write_file_stream to compress the file's data.
 */
ZPACK_EXPORT int zpack_write_file_stream_end(zpack_writer* writer, char* filename, zpack_compress_options* options, zpack_stream* stream, void* cctx);

/**
 * Write the central directory record.
 * @param writer The writer.
 */
ZPACK_EXPORT int zpack_write_cdr(zpack_writer* writer);

/**
 * (Ex) Write the central directory record.\n
 * Note: If unsure, use @ref zpack_write_cdr instead.
 * @param writer The writer.
 * @param entries File entries.
 * @param file_count File count.
 * @see zpack_write_cdr
 */
ZPACK_EXPORT int zpack_write_cdr_ex(zpack_writer* writer, zpack_file_entry* entries, zpack_u64 file_count);

/**
 * Write the end of central directory record.
 * @param writer The writer.
 */
ZPACK_EXPORT int zpack_write_eocdr(zpack_writer* writer);

/**
 * (Ex) Write the end of central directory record.\n
 * Note: If unsure, use @ref zpack_write_eocdr instead.
 * @param writer The writer.
 * @param cdr_offset Offset of the central directory record from the start of the archive.
 * @see zpack_write_eocdr
 */
ZPACK_EXPORT int zpack_write_eocdr_ex(zpack_writer* writer, zpack_u64 cdr_offset);


/**
 * Writes the entire archive in one go; basically a wrapper for all of the zpack_write* steps.
 * This uses the one-shot API to compress the files in memory. If you need something more flexible
 * or need to use the streaming API, use the other write functions yourself to incrementally
 * write the archive.
 * @param writer The writer.
 * @param files Files to be written to the archive.
 * @param file_count File count.
 * @return A return code (see @ref zpack_result)
 */
ZPACK_EXPORT int zpack_write_archive(zpack_writer* writer, zpack_file* files, zpack_u64 file_count);

/**
 * Closes the writer, releasing all resources previously occupied by it. This will make the writer
 * ready to be reused for another session.
 * @param writer The writer.
 */
ZPACK_EXPORT void zpack_close_writer(zpack_writer* writer);

/** @} */ // writer

/** @defgroup stream Stream
 *  zpack_stream and stream management functions.
 *  @{
 */

/**
 * Initializes the stream.
 * @param stream The stream.
 * @return A return code (see @ref zpack_result)
 */
ZPACK_EXPORT int zpack_init_stream(zpack_stream* stream);

/**
 * Resets the stream. Must be called after (de)compressing a file to be usable again.
 * @param stream The stream.
 */
ZPACK_EXPORT void zpack_reset_stream(zpack_stream *stream);

/**
 * Closes the stream. This does not free the buffers in next_in and next_out.
 * @param stream The stream.
 */
ZPACK_EXPORT void zpack_close_stream(zpack_stream* stream);

/** @} */ // stream

// Utils //

/** @defgroup utils Utils
 *  @{
 */

/**
 * Gets the recommended input size for decompression.
 * @param method The compression method to get the size for. Passing ZPACK_COMPRESSION_NONE will
                 return the largest size available.
 */
ZPACK_EXPORT size_t zpack_get_dstream_in_size(zpack_compression_method method);

/**
 * Gets the recommended output size for decompression.
 * @param method The compression method to get the size for. Passing ZPACK_COMPRESSION_NONE will
                 return the largest size available.
 */
ZPACK_EXPORT size_t zpack_get_dstream_out_size(zpack_compression_method method);

/**
 * Gets the recommended input size for compression.
 * @param method The compression method to get the size for. Passing ZPACK_COMPRESSION_NONE will
                 return the largest size available.
 */
ZPACK_EXPORT size_t zpack_get_cstream_in_size(zpack_compression_method method);

/**
 * Gets the recommended output size for compression.
 * @param method The compression method to get the size for. Passing ZPACK_COMPRESSION_NONE will
                 return the largest size available.
 */
ZPACK_EXPORT size_t zpack_get_cstream_out_size(zpack_compression_method method);

/**
 * Gets the first file entry with the specified filename. This does a simple linear lookup.
 * @param filename The filename to look for.
 * @param file_entries List of file entries.
 * @param file_count File count.
 * @return The file entry. Returns NULL if the file doesn't exist.
 */
ZPACK_EXPORT zpack_file_entry* zpack_get_file_entry(const char* filename, zpack_file_entry* file_entries, zpack_u64 file_count);

/**
 * Checks if a read stream is done. A macro is also available: see @ref ZPACK_READ_STREAM_DONE
 * @param stream The stream.
 * @param entry Entry of the file being read.
 */
ZPACK_EXPORT zpack_bool zpack_read_stream_done(zpack_stream* stream, zpack_file_entry* entry);

/**
 * Checks if a read stream is done. A function is also available: see @ref zpack_read_stream_done
 */
#define ZPACK_READ_STREAM_DONE(stream, entry) \
    ((stream)->total_in == (entry)->comp_size && (stream)->read_back == 0)

/**
 * Creates a compression context for the specified compression method.
 * @param method The compression method.
 * @return The compression context. Returns NULL if the compression method is none or invalid.
 */
ZPACK_EXPORT void* zpack_create_cctx(zpack_compression_method method);

/**
 * Creates a decompression context for the specified compression method.
 * @param method The compression method.
 * @return The decompression context. Returns NULL if the compression method is none or invalid.
 */
ZPACK_EXPORT void* zpack_create_dctx(zpack_compression_method method);

/**
 * Frees a compression context.
 * @param method The context's compressor
 * @param cctx The compression context
 */
ZPACK_EXPORT void zpack_free_cctx(zpack_compression_method method, void* cctx);

/**
 * Frees a decompression context.
 * @param method The context's compressor
 * @param dctx The decompression context
 */
ZPACK_EXPORT void zpack_free_dctx(zpack_compression_method method, void* dctx);
    
#if defined(_WIN32) && !defined(ZPACK_DISABLE_UNICODE)
/**
 * Converts a Windows wide char path to a UTF-8 formatted multibyte path. Needed for opening files
 * with Unicode characters in their name.\n
 * <b>Note:</b> This function is only available on Windows, with Unicode support enabled.
 * @param buffer Output for the UTF-8 path.
 * @param len Length of the output buffer.
 * @param input The original wide char path.
 * @return The value returned by <a href="https://docs.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-widechartomultibyte">WideCharToMultiByte</a>.
 */
ZPACK_EXPORT int zpack_convert_wchar_to_utf8(char *buffer, size_t len, const wchar_t* input);
#endif

/** @} */ // utils

#ifdef __cplusplus
}
#endif

#endif // __ZPACK_H__
